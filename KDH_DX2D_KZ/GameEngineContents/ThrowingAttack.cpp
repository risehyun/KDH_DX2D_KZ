#include "PreCompile.h"
#include "ThrowingAttack.h"
#include "UI_PlayUI.h"

ThrowingAttack::ThrowingAttack()
{
}

ThrowingAttack::~ThrowingAttack()
{
}

void ThrowingAttack::EnemyAttackEvent()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		ThrowingAttack* AttackPtr = dynamic_cast<ThrowingAttack*>(thisActor);

		AttackPtr->Death();
	};

	ThrowingAttackCollision->CollisionEvent(ContentsCollisionType::EnemyBody, Event);

}

void ThrowingAttack::Start()
{
	AttackName = UI_PlayUI::PlayUI->GetItemInfoInSlot();
	ThrowingAttackRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	ThrowingAttackRenderer->SetSprite(AttackName);

	if (AttackName != "spr_knife_0.png")
	{
		ThrowingAttackRenderer->Transform.SetLocalRotation({0.0f, 0.0f, 90.0f});
	}

	ThrowingAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerAttack);
	ThrowingAttackCollision->Transform.SetLocalScale({ 50, 50, 1 });
}

void ThrowingAttack::Update(float _Delta)
{
	EnemyAttackEvent();

	NextPos = { ThrowingAttackDir * _Delta * Speed };

	Transform.AddLocalPosition(NextPos);
	
	if (GetLiveTime() > 2.0f)
	{
		Death();
	}
}