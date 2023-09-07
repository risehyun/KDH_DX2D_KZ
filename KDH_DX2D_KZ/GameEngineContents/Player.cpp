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
//		MainSpriteRenderer->AutoSpriteSizeOn();


		MainSpriteRenderer->Transform.SetLocalScale({36 * 1.5f, 40 * 1.5f});
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });










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
	//float Speed = 100.0f;

	//if (GameEngineInput::IsPress('A'))
	//{
	//	Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('D'))
	//{
	//	Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('W'))
	//{
	//	Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('S'))
	//{
	//	Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	//}

	//if (GameEngineInput::IsPress('Q'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	//}

	//if (GameEngineInput::IsPress('E'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	//}











//	Gravity(_Delta);


	StateUpdate(_Delta);

	CameraFocus();


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
	default:
		break;
	}
}

void Player::DirCheck()
{
}

void Player::ChangeAnimationState(std::string_view _StateName)
{
}
