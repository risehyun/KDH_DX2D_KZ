#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Enemy.h"
#include "ContentsEnum.h"

#include "PlayerAttack.h"
#include "UI_Mouse.h"

Player* Player::MainPlayer = nullptr;
Player::Player() 
{
	MainPlayer = this;
	SetCharacterType(CharacterType::Player);
}

Player::~Player() 
{
}

void Player::CameraFocus()
{
	float4 TargetPos = Transform.GetWorldPosition();
	float4 NextPos = TargetPos;

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// 카메라가 맵 크기 이상 넘어가는 현상 방지
	// 왼쪽
	if (HalfWindowScale.X >= TargetPos.X)
	{
		NextPos.X = HalfWindowScale.X;
	}

	// 오른쪽
	else if (MapTexture->GetScale().X - HalfWindowScale.X <= TargetPos.X)
	{
		NextPos.X = MapTexture->GetScale().X - HalfWindowScale.X;
	}

	// 아래쪽
	if (MapTexture->GetScale().Y <= TargetPos.Y)
	{
		NextPos.Y = -(MapTexture->GetScale().Y - HalfWindowScale.Y);
	}

	// 위쪽
	else if (0.0f >= TargetPos.Y)
	{
		NextPos.Y = -HalfWindowScale.Y;
	}

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(NextPos);


}

void Player::Start()
{
	PlayerBodyCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerBody);
	PlayerBodyCollision->Transform.SetLocalScale({ 30, 30, 1 });
	PlayerBodyCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });

	PlayerParryingCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerParrying);
	PlayerParryingCollision->Transform.SetLocalScale({ 300, 100, 1 });
	PlayerParryingCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}
	

	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		MainSpriteRenderer->CreateAnimation("Idle", "spr_dragon_idle");

		MainSpriteRenderer->CreateAnimation("IdleToRun", "spr_dragon_idle_to_run");
		MainSpriteRenderer->CreateAnimation("RunToIdle", "spr_dragon_run_to_idle");

		MainSpriteRenderer->CreateAnimation("Run", "spr_dragon_run");
		MainSpriteRenderer->CreateAnimation("Jump", "spr_dragon_jump");
		MainSpriteRenderer->CreateAnimation("Fall", "spr_dragon_fall");
		MainSpriteRenderer->CreateAnimation("Roll", "spr_dragon_roll");
		MainSpriteRenderer->CreateAnimation("Attack", "spr_dragon_attack");
		MainSpriteRenderer->CreateAnimation("Dash", "spr_dragon_dash");
		MainSpriteRenderer->CreateAnimation("Death", "spr_dragon_hurtground");

		MainSpriteRenderer->CreateAnimation("DoorKick", "spr_dragon_doorkick", 0.1f, 2, 5, true);
		MainSpriteRenderer->CreateAnimation("Precrouch", "spr_dragon_precrouch", 0.1f, 0, 1, false);
		MainSpriteRenderer->CreateAnimation("Postcrouch", "spr_dragon_postcrouch", 0.1f, 0, 1, false);
		MainSpriteRenderer->SetImageScale({ 62, 65 });
	}

	{
		PlayerFXRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		PlayerFXRenderer->CreateAnimation("JumpCloud", "spr_player_jumpcloud", 0.1f, 0, 3, false);
		PlayerFXRenderer->CreateAnimation("LandCloud", "spr_player_landcloud", 0.1f, 0, 6, false);
		PlayerFXRenderer->CreateAnimation("RunCloud", "spr_player_dustcloud", 0.1f, 0, 6, true);


		PlayerFXRenderer->AutoSpriteSizeOn();
		PlayerFXRenderer->Transform.SetLocalPosition({ 0.0f, -10.0f, 0.0f, 1.0f });
		PlayerFXRenderer->Off();
	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_dragon_dash_range.png"));
			GameEngineSprite::CreateSingle("spr_dragon_dash_range.png");
		}
	}




	PlayerRenderer_Dash = CreateComponent<GameEngineSpriteRenderer>(30);
	PlayerRenderer_Dash->SetSprite("spr_dragon_dash_range.png");
	PlayerRenderer_Dash->Transform.SetLocalPosition({ 0, 0 });
	PlayerRenderer_Dash->AutoSpriteSizeOn();
	PlayerRenderer_Dash->Off();





	// Fx Sound 파일
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\FX\\PlayerFX\\");
	
		if (nullptr == GameEngineSound::FindSound("sound_player_jump.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_jump.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_land.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_land.wav"));
		}


		if (nullptr == GameEngineSound::FindSound("sound_player_running_1.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_1.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_running_2.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_2.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_running_3.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_3.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_running_4.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_4.wav"));
		}
	}

	//// 충돌 디버그용 렌더러
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\");
	{
		GameEngineTexture::Load(FilePath.PlusFilePath("Test.bmp"));
		GameEngineSprite::CreateSingle("Test.bmp");
	}

	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Left = CreateComponent<GameEngineSpriteRenderer>(30);
	DebugRenderer_Left->AutoSpriteSizeOn();
	DebugRenderer_Left->SetSprite("Test.bmp");
	DebugRenderer_Left->Transform.SetLocalPosition(LeftCheck);

	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Right = CreateComponent<GameEngineSpriteRenderer>(30);
	DebugRenderer_Right->AutoSpriteSizeOn();
	DebugRenderer_Right->SetSprite("Test.bmp");
	DebugRenderer_Right->Transform.SetLocalPosition(RightCheck);

	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Up = CreateComponent<GameEngineSpriteRenderer>(30);
	DebugRenderer_Up->AutoSpriteSizeOn();
	DebugRenderer_Up->SetSprite("Test.bmp");
	DebugRenderer_Up->Transform.SetLocalPosition(UpCheck);

	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Down = CreateComponent<GameEngineSpriteRenderer>(30);
	DebugRenderer_Down->AutoSpriteSizeOn();
	DebugRenderer_Down->SetSprite("Test.bmp");
	DebugRenderer_Down->Transform.SetLocalPosition(DownCheck);

	MainSpriteRenderer->ChangeAnimation("Idle");

	ChangeState(PlayerState::Idle);
}

void Player::Update(float _Delta)
{
	GameEngineDebug::DrawBox2D(MainSpriteRenderer->Transform);

//	Gravity(_Delta);
	DirCheck();

	StateUpdate(_Delta);

	CameraFocus();

	EventParameter BodyCollisionEvent;

	BodyCollisionEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* EnemyAttackActor = Col->GetActor();
	//	EnemyAttackActor->Death();

		GameEngineActor* thisActor = _this->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

	//	PlayerPtr->ChangeState(PlayerState::Death);


	};

	PlayerBodyCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, BodyCollisionEvent);



	EventParameter ParryCollisionEvent;

	ParryCollisionEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* thisActor = _this->GetActor();
			Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

			PlayerPtr->OnParryable();

		};

	ParryCollisionEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{

			GameEngineActor* thisActor = _this->GetActor();
			Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

			PlayerPtr->OffParryable();

		};

	PlayerParryingCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, ParryCollisionEvent);



	//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetWorldPosition());

	//float4 WorldMousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	//OutputDebugStringA(WorldMousePos.ToString("\n").c_str());





}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;

		case PlayerState::Run:
			RunStart();
			break;

		case PlayerState::Jump:
			JumpStart();
			break;

		case PlayerState::Fall:
			FallStart();
			break;

		case PlayerState::Roll:
			RollStart();
			break;

		case PlayerState::Attack:
			AttackStart();
			break;

		case PlayerState::Dash:
			DashStart();
			break;

		case PlayerState::Death:
			DeathStart();
			break;

		case PlayerState::Doorkick:
			DoorKickStart();
			break;

		case PlayerState::IdleToRun:
			IdleToRunStart();
			break;

		case PlayerState::RunToIdle:
			RunToIdleStart();
			break;

		case PlayerState::PostCrouch:
			PostCrouchStart();
			break;

		case PlayerState::PreCrouch:
			PreCrouchStart();
			break;

		default:
			break;
		}
	}

	State = _State;
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	
	case PlayerState::Run:
		return RunUpdate(_Delta);
	
	case PlayerState::Jump:
		return JumpUpdate(_Delta);

	case PlayerState::Fall:
		return FallUpdate(_Delta);

	case PlayerState::Roll:
		return RollUpdate(_Delta);
	
	case PlayerState::Attack:
		return AttackUpdate(_Delta);

	case PlayerState::Dash:
		return DashUpdate(_Delta);

	case PlayerState::Death:
		return DeathUpdate(_Delta);

	case PlayerState::Doorkick:
		return DoorKickUpdate(_Delta);

	case PlayerState::IdleToRun:
		return IdleToRunUpdate(_Delta);

	case PlayerState::RunToIdle:
		return RunToIdleUpdate(_Delta);

	case PlayerState::PreCrouch:
		return PreCrouchUpdate(_Delta);

	case PlayerState::PostCrouch:
		return PostCrouchUpdate(_Delta);

	default:
		break;
	}
}

void Player::DirCheck()
{

	// 방향을 결정하는 키들이 모두 프리라면 그상태 그대로 유지. 아래의 D가 프리일때 Left가 되는 것을 방지.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A가 눌렸거나 D가 프리이라면 Left로 방향전환 인데 가만히있어도 Left를 바라보는 현상이 생김.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		SetPlayerDir(Dir);
		MainSpriteRenderer->SetImageScale({ 72, 65 });
		MainSpriteRenderer->LeftFlip();
		return;
	}

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		SetPlayerDir(Dir);
		MainSpriteRenderer->SetImageScale({ 72, 65 });
		MainSpriteRenderer->RightFlip();
		return;
	}
}