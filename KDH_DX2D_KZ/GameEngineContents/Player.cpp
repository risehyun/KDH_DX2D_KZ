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
}

Player::~Player() 
{
}

void Player::CameraFocus()
{
	float4 TargetPos = Transform.GetWorldPosition();
	float4 NextPos = TargetPos;

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// ī�޶� �� ũ�� �̻� �Ѿ�� ���� ����
	// ����
	if (HalfWindowScale.X >= TargetPos.X)
	{
		NextPos.X = HalfWindowScale.X;
	}

	// ������
	else if (MapTexture->GetScale().X - HalfWindowScale.X <= TargetPos.X)
	{
		NextPos.X = MapTexture->GetScale().X - HalfWindowScale.X;
	}

	// �Ʒ���
	if (MapTexture->GetScale().Y <= TargetPos.Y)
	{
		NextPos.Y = -(MapTexture->GetScale().Y - HalfWindowScale.Y);
	}

	// ����
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

	PlayerParryingCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerParrying);
	PlayerParryingCollision->Transform.SetLocalScale({ 30, 30, 1 });
	PlayerParryingCollision->Transform.SetLocalPosition({ PlayerParryingCollision->Transform.GetWorldPosition().X - 800.0f, PlayerParryingCollision->Transform.GetWorldPosition().Y + 370.f});


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
		MainSpriteRenderer->CreateAnimation("Run", "spr_dragon_run");
		MainSpriteRenderer->CreateAnimation("Jump", "spr_dragon_jump");
		MainSpriteRenderer->CreateAnimation("Fall", "spr_dragon_fall");
		MainSpriteRenderer->CreateAnimation("Roll", "spr_dragon_roll");
		MainSpriteRenderer->CreateAnimation("Attack", "spr_dragon_attack");
		MainSpriteRenderer->CreateAnimation("Dash", "spr_dragon_dash");
		MainSpriteRenderer->CreateAnimation("Death", "spr_dragon_hurtground");

		MainSpriteRenderer->Transform.SetLocalScale({36 * 3.f, 40 * 3.f});
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















	//// �浹 ����׿� ������

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
	DebugRenderer_Left->Transform.SetLocalPosition(PlayerParryingCollision->Transform.GetWorldPosition());


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
//	MainSpriteRenderer->SetViewCameraSelect(100);

	ChangeState(PlayerState::Idle);
}

void Player::Update(float _Delta)
{
	
//	Gravity(_Delta);
	DirCheck();

	StateUpdate(_Delta);

	CameraFocus();

	EventParameter BodyCollisionEvent;

	BodyCollisionEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{


		//GameEngineActor* thisActor = _this->GetActor();
		//Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		//PlayerPtr->ChangeState(PlayerState::Death);


	};

	PlayerBodyCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, BodyCollisionEvent);






	//EventParameter ParryingCollisionEvent;

	//ParryingCollisionEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	//{

	///*	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	//	{*/
	//		GameEngineActor* thisActor = _this->GetActor();
	//		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

	//		PlayerPtr->ChangeState(PlayerState::Roll);
	////	}

	//};

	//PlayerParryingCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, ParryingCollisionEvent);

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

	default:
		break;
	}
}

void Player::DirCheck()
{

	// ������ �����ϴ� Ű���� ��� ������� �׻��� �״�� ����. �Ʒ��� D�� �����϶� Left�� �Ǵ� ���� ����.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A�� ���Ȱų� D�� �����̶�� Left�� ������ȯ �ε� �������־ Left�� �ٶ󺸴� ������ ����.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		MainSpriteRenderer->Transform.SetLocalScale( {-36 * 1.5f, 40 * 1.5f} );
		return;
	}

	// D�� ���Ȱų� A�� �����̸� Right�� ���� ��ȯ.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		MainSpriteRenderer->Transform.SetLocalScale({ 36 * 1.5f, 40 * 1.5f} );
		return;
	}
}

void Player::ChangeAnimationState(std::string_view _StateName)
{
}
