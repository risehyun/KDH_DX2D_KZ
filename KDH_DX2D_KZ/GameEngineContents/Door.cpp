#include "PreCompile.h"
#include "Door.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"
#include "Enemy.h"

Door::Door()
{

}

Door::~Door()
{
}

void Door::SetDoorType(EDoorType _Type)
{
	Type = _Type;

	if (Type == EDoorType::Normal)
	{

		DoorMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));

		DoorMainRenderer->CreateAnimation("DoorIdle", "spr_door_animation", 0.1f, 0, 0, true);
		DoorMainRenderer->CreateAnimation("DoorOpen", "spr_door_animation", 0.01f, 1, 19, false);

		DoorMainRenderer->AutoSpriteSizeOn();

		DoorMainRenderer->ChangeAnimation("DoorIdle");
	}

	else if (Type == EDoorType::Iron)
	{

		DoorMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));

		DoorMainRenderer->CreateAnimation("DoorIdle", "spr_door_animation_iron", 0.1f, 0, 0, true);
		DoorMainRenderer->CreateAnimation("DoorOpen", "spr_door_animation_iron", 0.01f, 1, 19, false);

		DoorMainRenderer->AutoSpriteSizeOn();

		DoorMainRenderer->ChangeAnimation("DoorIdle");
	}

}

void Door::Start()
{
	GameEngineInput::AddInputObject(this);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	DoorGlowRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));
	DoorGlowRenderer->CreateAnimation("DoorGlow1", "spr_door_glow", 0.1f, 0, 0, false);
	DoorGlowRenderer->AutoSpriteSizeOn();
	DoorGlowRenderer->ChangeAnimation("DoorGlow1");

	DoorMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	DoorMainCollision->Transform.SetLocalScale({ 100, 100, 1 });

}

void Door::Update(float _Delta)
{
	DoorAutoOpenEvent();
	DoorAttackOpenEvent();
}

void Door::DoorAutoOpenEvent()
{
	EventParameter DoorAutoOpenEvent;

	DoorAutoOpenEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

	};

	DoorAutoOpenEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* PlayerActor = Col->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(PlayerActor);

		GameEngineActor* thisActor = _this->GetActor();
		Door* DoorPtr = dynamic_cast<Door*>(thisActor);

		// ★ 문제 생길 수 있음
		if (true == GameEngineInput::IsPress('D', thisActor))
		{
			DoorPtr->DoorPushTimer += GameEngineCore::MainTime.GetDeltaTime();

			if (DoorPtr->DoorPushTimer > 0.1f)
			{
				DoorPtr->DoorMainRenderer->ChangeAnimation("DoorOpen");
				DoorPtr->DoorGlowRenderer->Off();
				DoorPtr->DoorMainCollision->Off();

				PlayerPtr->FSM_PlayerState.ChangeState(FSM_PlayerState::DoorKick);
				return;
			}
		}


	};

	DoorMainCollision->CollisionEvent(ContentsCollisionType::PlayerBody, DoorAutoOpenEvent);

}

void Door::DoorAttackOpenEvent()
{

	EventParameter DoorAttackOpenEvent;

	DoorAttackOpenEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Door* DoorPtr = dynamic_cast<Door*>(thisActor);

		DoorPtr->DoorMainRenderer->ChangeAnimation("DoorOpen");
		DoorPtr->DoorMainCollision->Off();
		DoorPtr->DoorGlowRenderer->Off();

	};


	DoorMainCollision->CollisionEvent(ContentsCollisionType::PlayerAttack, DoorAttackOpenEvent);

}

