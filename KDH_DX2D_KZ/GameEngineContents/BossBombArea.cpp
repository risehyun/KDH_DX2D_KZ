#include "PreCompile.h"
#include "BossBombArea.h"
#include "Player.h"

BossBombArea::BossBombArea()
{
}

BossBombArea::~BossBombArea()
{
}

void BossBombArea::Start()
{
	BossBombAreaCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::BossBombArea);
	BossBombAreaCollision->SetCollisionType(ColType::SPHERE2D);
	BossBombAreaCollision->Transform.SetLocalScale({ 270.0f, 270.0f });
	BossBombAreaCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });
}

void BossBombArea::Update(float _Delta)
{

	if (GetLiveTime() > 1.0f)
	{
		Death();
	}

	BossBombDamagedEvent();
}

void BossBombArea::BossBombDamagedEvent()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = Col->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		GameEngineActor* AttackActor = _this->GetActor();

		if (true == PlayerPtr->IsImmortal)
		{
			return;
		}

		if (false == PlayerPtr->GetMainRenderer()->IsCurAnimation("Death"))
		{
			PlayerPtr->FSM_PlayerState.ChangeState(FSM_PlayerState::Death);
			AttackActor->Death();
		}

	};

	BossBombAreaCollision->CollisionEvent(ContentsCollisionType::PlayerBody, Event);

}