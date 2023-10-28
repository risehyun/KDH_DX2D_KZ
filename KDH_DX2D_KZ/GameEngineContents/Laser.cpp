#include "PreCompile.h"
#include "Laser.h"
#include "Player.h"

Laser::Laser()
{
}

Laser::~Laser()
{
}

void Laser::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\Object\\Laser\\");
	{
		GameEngineTexture::Load(FilePath.PlusFilePath("spr_ceiling_laser_on.png"));
		GameEngineSprite::CreateSingle("spr_ceiling_laser_on.png");
	}

	LaserCeilingRenderer_Top = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::PlayFront));
	LaserCeilingRenderer_Top->SetSprite("spr_ceiling_laser_on.png");
	LaserCeilingRenderer_Top->Transform.SetLocalPosition({ 0.0f, 85.0f });
	LaserCeilingRenderer_Top->AutoSpriteSizeOn();
	LaserCeilingRenderer_Top->On();


	LaserMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	LaserMainRenderer->Transform.SetLocalPosition({ 0.0f, -10.0f });
	LaserMainRenderer->CreateAnimation("LaserFlow", "NoCollision");
	LaserMainRenderer->CreateAnimation("LaserDetect", "Collision");
	LaserMainRenderer->AutoSpriteSizeOn();
	LaserMainRenderer->ChangeAnimation("LaserFlow");

	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->Transform.SetLocalScale({ 100, 100, 1 });

}

void Laser::Update(float _Delta)
{
	LaserDetectEnemyEvent();
}

void Laser::LaserDetectEnemyEvent()
{
	EventParameter LaserDetectEnemyEvent;

	LaserDetectEnemyEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* thisActor = _this->GetActor();
			Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserDetect");
 
			// Player::MainPlayer->FSM_PlayerState.ChangeState(FSM_PlayerState::Death);


		};

	//LaserDetectEnemyEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	//	{
	//		//GameEngineActor* PlayerActor = Col->GetActor();
	//		//Player* PlayerPtr = dynamic_cast<Player*>(PlayerActor);

	//		//GameEngineActor* thisActor = _this->GetActor();
	//		//Door* DoorPtr = dynamic_cast<Door*>(thisActor);
	//	};

	LaserDetectEnemyEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* thisActor = _this->GetActor();
			Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserFlow");

			// Player::MainPlayer->FSM_PlayerState.ChangeState(FSM_PlayerState::Death);


		};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, LaserDetectEnemyEvent);
}
