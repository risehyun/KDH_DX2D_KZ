#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>


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


	TestCollision = CreateComponent<GameEngineComponent>(30);
	TestCollision->Transform.SetLocalScale({ 30, 30, 1 });

	Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
	Col->Transform.SetLocalScale({ -100.0f, 100.0f, 1.0f });

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

		//		MainSpriteRenderer->AutoSpriteSizeOn();

		MainSpriteRenderer->Transform.SetLocalScale({ 36 * 1.5f, 40 * 1.5f });
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

	//	Gravity(_Delta);
	DirCheck();

	StateUpdate(_Delta);

	CameraFocus();

	// 몬스터가 몬스터랑 충돌하고 싶으면?
// 내 미래의 위치

	//EventParameter Event;

	//Event.Enter = [](GameEngineCollision* Col)
	//	{
	//		int a = 0;
	//	};

	//Event.Stay = [](GameEngineCollision* Col)
	//	{
	//		int a = 0;
	//	};


	//Event.Exit = [](GameEngineCollision* Col)
	//	{
	//		Col->GetActor()->Death();

	//		int a = 0;
	//	};

	//Col->CollisionEvent(ContentsCollisionType::Monster, Event);
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
		break;

	case PlayerState::Fall:
		return FallUpdate(_Delta);
		break;

	case PlayerState::Roll:
		return RollUpdate(_Delta);
		break;

	case PlayerState::Attack:
		return AttackUpdate(_Delta);
		break;

	case PlayerState::Dash:
		return DashUpdate(_Delta);

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
		MainSpriteRenderer->Transform.SetLocalScale({ -36 * 1.5f, 40 * 1.5f });
		//	ChangeAnimationState(CurState);
		return;
	}

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		MainSpriteRenderer->Transform.SetLocalScale({ 36 * 1.5f, 40 * 1.5f });
		//	ChangeAnimationState(CurState);
		return;
	}
}

void Player::ChangeAnimationState(std::string_view _StateName)
{
}
