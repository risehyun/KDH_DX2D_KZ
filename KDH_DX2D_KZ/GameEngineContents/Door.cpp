#include "PreCompile.h"
#include "Door.h"

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

		DoorMainRenderer->CreateAnimation("Door", "spr_door_animation");

		DoorMainRenderer->AutoSpriteSizeOn();
	}

	DoorMainRenderer->ChangeAnimation("Door");

	DoorMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	DoorMainCollision->Transform.SetLocalScale({ 30, 30, 1 });

}

void Door::Update(float _Delta)
{
}
