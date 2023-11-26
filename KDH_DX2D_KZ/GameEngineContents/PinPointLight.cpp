#include "PreCompile.h"
#include "PinPointLight.h"
#include "Player.h"
#include "GameStateManager.h"

PinPointLight::PinPointLight()
{
}

PinPointLight::~PinPointLight()
{
}

void PinPointLight::InitRotationDir(ERotationDir _Dir)
{
	Dir = _Dir;

	if (Dir == ERotationDir::Left)
	{
		// 움직임 범위는 -70(최초,오른쪽 방향 최대값) ~ -110(왼쪽 방향 최대값) 
		Transform.AddLocalRotation({ 0.0f, 0.0f, -110.0f });
		MoveDir = { 0.0f, 0.0f, 1.0f };
	}

	else
	{
		// 움직임 범위는 -70(최초,오른쪽 방향 최대값) ~ -110(왼쪽 방향 최대값) 
		Transform.AddLocalRotation({ 0.0f, 0.0f, -70.0f });
		MoveDir = { 0.0f, 0.0f, -1.0f };
	}

}

void PinPointLight::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Object\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("PinPointLight.png"));
		GameEngineSprite::CreateSingle("PinPointLight.png");

	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
		Renderer->SetSprite("PinPointLight.png");

		Renderer->AutoSpriteSizeOn();


	}

	DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	DetectCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	DetectCollision->Transform.SetLocalPosition({ 300.0f, 0.0f });
}

void PinPointLight::Update(float _Delta)
{
	DetectEvent(_Delta);
	RotateLight(_Delta);

	// ★ 역재생 끝나면 OFF된 충돌체가 다시 On이 되어야 한다
}

void PinPointLight::RotateLight(float _Delta)
{
	Transform.AddLocalRotation({ MoveDir * _Delta * Speed });

	if (Transform.GetLocalRotationEuler().Z < -110.0f)
	{
		MoveDir = { 0.0f, 0.0f, 1.0f };
	}

	if (Transform.GetLocalRotationEuler().Z > -70.0f)
	{
		MoveDir = { 0.0f, 0.0f, -1.0f };
	}
}



void PinPointLight::DetectEvent(float _Delta)
{
	EventParameter DectectLightEvent;

	DectectLightEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		if(true == GameStateManager::GameState->GetCurrentGameState())
		{
			return;
		}
	};

	DectectLightEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

		if(true == GameStateManager::GameState->GetCurrentGameState())
		{
			return;
		}

		else if (Player::MainPlayer->GetMainRenderer()->IsCurAnimation("PreCrouch"))
		{
			return;
		}

		else
		{
			//Player::MainPlayer->DebugRenderer_Reverse->On();
			//Player::MainPlayer->ReverseOn();
			//Player::MainPlayer->Reverse();
		//	Player::MainPlayer->ChangeState(PlayerState::Death);
		//	_this->Off();
			return;

		}

	};

	DectectLightEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

	};

	DetectCollision->CollisionEvent(ContentsCollisionType::PlayerBody, DectectLightEvent);


}
