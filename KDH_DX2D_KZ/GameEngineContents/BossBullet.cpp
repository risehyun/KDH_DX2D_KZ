#include "PreCompile.h"
#include "BossBullet.h"
#include "FX_Explosion.h"
#include "Boss.h"

BossBullet::BossBullet()
{
}

BossBullet::~BossBullet()
{
}

void BossBullet::Start()
{
	BossBulletRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

	BossBulletRenderer->CreateAnimation("FireBullet", "spr_bullet", 0.1f, 0, 4, false);
	BossBulletRenderer->AutoSpriteSizeOn();

	BossBulletRenderer->ChangeAnimation("FireBullet");
}

void BossBullet::Update(float _Delta)
{

	if (float4::LEFT == Boss::Boss_HeadHunter->GetBossDir())
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * 200.0f);
	}

	if (float4::RIGHT == Boss::Boss_HeadHunter->GetBossDir())
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * 200.0f);
	}

	if (GetLiveTime() > 2.0f)
	{
		Death();
	}
}