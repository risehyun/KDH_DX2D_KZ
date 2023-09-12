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
		DoorMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		DoorMainRenderer->CreateAnimation("DoorIdle", "spr_door_animation", 0.1, 0, 0, true);
		DoorMainRenderer->CreateAnimation("Door", "spr_door_animation", 0.1, 0, 19, true);

		DoorMainRenderer->AutoSpriteSizeOn();
	}

	DoorMainRenderer->ChangeAnimation("DoorIdle");

	DoorMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	DoorMainCollision->Transform.SetLocalScale({ 100, 100, 1 });

}

void Door::Update(float _Delta)
{
//	EventParameter Event;
//
//	Event.Enter = [](GameEngineCollision* Col)
//		{
//
//			GameEngineActor* thisActor = Col->GetActor();
//			Player* PlayerPtr = dynamic_cast<Player*>(thisActor);
//
//			PlayerPtr->ChangeState(PlayerState::Roll);
//
//
//
////			GameEngineActor* Actor = Col->GetActor();
//
////			Actor->
//		};
//
//	Event.Stay = [](GameEngineCollision* Col)
//		{
//			int a = 0;
//		};
//
//
//	Event.Exit = [](GameEngineCollision* Col)
//		{
//			int a = 0;
//		};
//
//	DoorMainCollision->CollisionEvent(ContentsCollisionType::Player, Event);
//










}
