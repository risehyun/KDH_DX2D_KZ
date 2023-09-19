#include "PreCompile.h"
#include "Door.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

Door::Door()
{

}

Door::~Door()
{
}

void Door::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		DoorMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));

		DoorMainRenderer->CreateAnimation("DoorIdle", "spr_door_animation", 0.1f, 0, 0, true);
		DoorMainRenderer->CreateAnimation("Door", "spr_door_animation", 0.01f, 1, 19, false);

		DoorMainRenderer->AutoSpriteSizeOn();
	}

	DoorMainRenderer->ChangeAnimation("DoorIdle");

	DoorMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	DoorMainCollision->Transform.SetLocalScale({ 100, 100, 1 });

}

void Door::Update(float _Delta)
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


		// ÀÛµ¿ X
//		DoorPtr->DoorMainCollision->Off();

		PlayerPtr->ChangeState(PlayerState::Doorkick);


		//if (DoorPtr->DoorPushTimer > 1.5f)
		//{
		DoorPtr->DoorMainRenderer->ChangeAnimation("Door");
		if (true == DoorPtr->DoorMainRenderer->IsCurAnimationEnd())
		{
			 DoorPtr->Off();
		}
		//		}


	};

	DoorMainCollision->CollisionEvent(ContentsCollisionType::PlayerBody, DoorAutoOpenEvent);



	EventParameter DoorAttackOpenEvent;

	DoorAttackOpenEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Door* DoorPtr = dynamic_cast<Door*>(thisActor);

		DoorPtr->DoorMainRenderer->ChangeAnimation("Door");
		DoorPtr->DoorMainCollision->Off();

		if (true == DoorPtr->DoorMainRenderer->IsCurAnimationEnd())
		{
			DoorPtr->Off();
		}

	};


	DoorMainCollision->CollisionEvent(ContentsCollisionType::PlayerAttack, DoorAttackOpenEvent);

}
