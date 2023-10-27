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


	LaserMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
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
