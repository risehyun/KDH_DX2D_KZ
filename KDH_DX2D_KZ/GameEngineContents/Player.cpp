#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Enemy.h"
#include "ContentsEnum.h"

#include "PlayerAttack.h"
#include "UI_Mouse.h"
#include "GameStateManager.h"

Player* Player::MainPlayer = nullptr;
Player::Player()
{
	MainPlayer = this;
	SetCharacterType(CharacterType::Player);
}

Player::~Player()
{
}

void Player::Start()
{
	GameEngineInput::AddInputObject(this);
	//	GetLevel()->GetMainCamera()->CameraTargetSetting(Transform, float4::BACKWARD * 500.0f);

	PlayerBodyCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerBody);
	PlayerBodyCollision->Transform.SetLocalScale({ 30, 30, 1 });
	PlayerBodyCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });

	PlayerParryingCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerParrying);
	PlayerParryingCollision->Transform.SetLocalScale({ 300, 100, 1 });
	PlayerParryingCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });

	PlayerDashCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerDash);
	PlayerDashCollision->SetCollisionType(ColType::LINE2D);

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
		MainSpriteRenderer->CreateAnimation("Death", "spr_dragon_hurtground", 0.1f, 0, 5, false);

		MainSpriteRenderer->CreateAnimation("DoorKick", "spr_dragon_doorkick", 0.1f, 2, 5, true);
		MainSpriteRenderer->CreateAnimation("PreCrouch", "spr_dragon_PreCrouch", 0.1f, 0, 1, false);
		MainSpriteRenderer->CreateAnimation("Postcrouch", "spr_dragon_postcrouch", 0.1f, 0, 1, false);
		MainSpriteRenderer->AutoSpriteSizeOn();

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



	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_ReverseText.png"));
			GameEngineSprite::CreateSingle("UI_ReverseText.png");
		}

		DebugRenderer_Reverse = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		DebugRenderer_Reverse->SetSprite("UI_ReverseText.png");
		DebugRenderer_Reverse->Transform.SetLocalPosition({ 0.0f, 40.0f });
		DebugRenderer_Reverse->Off();
	}

	{
		//// 충돌 디버그용 렌더러
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("Test.bmp"));
			GameEngineSprite::CreateSingle("Test.bmp");

			GameEngineTexture::Load(FilePath.PlusFilePath("spr_cursor_slash.png"));
			GameEngineSprite::CreateSingle("spr_cursor_slash.png");

			GameEngineTexture::Load(FilePath.PlusFilePath("DashLine.png"));
			GameEngineSprite::CreateSingle("DashLine.png");
		}


		

		PlayerRenderer_DashLine = CreateComponent<GameEngineSpriteRenderer>(30);
		PlayerRenderer_DashLine->AutoSpriteSizeOn();
		PlayerRenderer_DashLine->SetSprite("DashLine.png");


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

	}

//	AddReverseRenderer(MainSpriteRenderer);


	// FSM 등록
	FSM_Player_Idle();
	FSM_Player_PreCrouch();
	FSM_Player_Roll();
	FSM_Player_Jump();
	FSM_Player_Fall();
	FSM_Player_Run();
	FSM_Player_Dash();
	FSM_Player_Attack();
	FSM_Player_DoorKick();

	FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
//	ChangeState(PlayerState::Idle);
}

void Player::Update(float _Delta)
{
	FSM_PlayerState.Update(_Delta);

	if (true == IsOnDashCoolTimeDecrease)
	{
		if (CurPlayerDashCoolTime <= MaxPlayerDashCoolTime)
		{
			CurPlayerDashCoolTime += _Delta;

			if (CurPlayerDashCoolTime > MaxPlayerDashCoolTime)
			{
				CurPlayerDashCoolTime = 0.0f;
				IsOnDashCoolTimeDecrease = false;
			}
		}

		
	}




	PlayerParryEvent();
	PlayerDamagedEvent();



	//if (true == GameStateManager::GameState->GetCurrentGameState())
	//{
	//	DebugRenderer_Reverse->On();
	//	ReverseOn();
	//	Reverse();
	//	return;
	//}

	//else
	//{
	//	ReverseOff();
	//	DebugRenderer_Reverse->Off();
	//}
	//	GameEngineDebug::DrawBox2D(MainSpriteRenderer->Transform);

		//	Gravity(_Delta);
	//DirCheck();

	//StateUpdate(_Delta);



//	UpdateAddingReverseData(_Delta);
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
	if (GameEngineInput::IsFree('A', this) && true == GameEngineInput::IsFree('D', this))
	{
		return;
	}

	// A가 눌렸거나 D가 프리이라면 Left로 방향전환 인데 가만히있어도 Left를 바라보는 현상이 생김.
	if (GameEngineInput::IsDown('A', this) || GameEngineInput::IsFree('D', this))
	{
		Dir = PlayerDir::Left;
		SetPlayerDir(Dir);
		MainSpriteRenderer->LeftFlip();
		return;
	}

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
	if (GameEngineInput::IsDown('D', this) || GameEngineInput::IsFree('A', this))
	{
		Dir = PlayerDir::Right;
		SetPlayerDir(Dir);
		MainSpriteRenderer->RightFlip();
		return;
	}
}

void Player::PlayerDamagedEvent()
{
	EventParameter BodyCollisionEvent;

	BodyCollisionEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* EnemyAttackActor = Col->GetActor();
			//	EnemyAttackActor->Death();

			GameEngineActor* thisActor = _this->GetActor();
			Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

			//PlayerPtr->ChangeState(PlayerState::Death);


		};

	PlayerBodyCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, BodyCollisionEvent);
}

void Player::PlayerParryEvent()
{
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
}

void Player::PlayerDashAttackEvent()
{
	EventParameter DashCollisionEvent;
	float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();

	DashCollisionEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

		GameEngineActor* EnemyActor = Col->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(EnemyActor);

		if (true == EnemyPtr->IsEnemyDeath)
		{
			return;
		}
		
		EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
		return;
			//->ChangeEmotion(EEnemyState_Emotion::HardExclamation);

	};

	DashCollisionEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

	};

	PlayerDashCollision->CollisionLineEvent(ContentsCollisionType::EnemyBody, End, DashCollisionEvent);

}