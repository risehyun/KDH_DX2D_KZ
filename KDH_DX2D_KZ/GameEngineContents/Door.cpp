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
		DoorMainRenderer->CreateAnimation("Door", "spr_door_animation", 0.1f, 0, 19, false);

		DoorMainRenderer->AutoSpriteSizeOn();
	}

	DoorMainRenderer->ChangeAnimation("DoorIdle");

	DoorMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	DoorMainCollision->Transform.SetLocalScale({ 100, 100, 1 });

}

void Door::Update(float _Delta)
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{

			//GameEngineActor* thisActor = Col->GetActor();
			//Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

			//PlayerPtr->ChangeState(PlayerState::Roll);

		};

	Event.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* PlayerActor = Col->GetActor();
			Player* PlayerPtr = dynamic_cast<Player*>(PlayerActor);

			GameEngineActor* thisActor = _this->GetActor();
			Door* DoorPtr = dynamic_cast<Door*>(thisActor);

	//		DoorPtr->DoorPushTimer += GameEngineCore::MainTime.GetDeltaTime();


			//if (DoorPtr->DoorPushTimer > 3.f)
			//{
				DoorPtr->DoorMainRenderer->ChangeAnimation("Door");
				if (true == DoorPtr->DoorMainRenderer->IsCurAnimationEnd())
				{
				//	DoorPtr->Off();
				}
		//	}
		};


	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			int a = 0;
		};

	DoorMainCollision->CollisionEvent(ContentsCollisionType::PlayerBody, Event);











}
