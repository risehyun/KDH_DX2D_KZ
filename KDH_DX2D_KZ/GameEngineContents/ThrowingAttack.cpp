#include "PreCompile.h"
#include "ThrowingAttack.h"
#include "UI_PlayUI.h"

ThrowingAttack::ThrowingAttack()
{
}

ThrowingAttack::~ThrowingAttack()
{
}

void ThrowingAttack::InitThrowingAttackData(float4 _ThrowingAttackDir, float _DurationTime)
{
}

void ThrowingAttack::Start()
{
	AttackName = UI_PlayUI::PlayUI->GetItemInfoInSlot();
	ThrowingAttackRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	ThrowingAttackRenderer->SetSprite(AttackName);

	ThrowingAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerAttack);
	ThrowingAttackCollision->Transform.SetLocalScale({ 50, 50, 1 });
}

void ThrowingAttack::Update(float _Delta)
{
	Transform.AddLocalPosition(ThrowingAttackDir * _Delta * Speed);

	if (GetLiveTime() > 2.0f)
	{
		Death();
	}
}