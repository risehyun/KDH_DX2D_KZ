#include "PreCompile.h"
#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::DirCheck()
{
}

void Boss::Start()
{
	BossMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossMainRenderer->AutoSpriteSizeOn();

	BossMainRenderer->CreateAnimation("Idle", "spr_headhunter_idle");
	BossMainRenderer->CreateAnimation("PutBackRifle", "spr_headhunter_putbackrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("TakeOutRifle", "spr_headhunter_takeoutrifle", 0.1f, 0, 7, false);

	
//	BossMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);
//	BossMainRenderer->CreateAnimation("Turn", "spr_gangsterturn", 0.2f, 0, 5, false);

	

	BossMainRenderer->ChangeAnimation("TakeOutRifle");



	BossEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossEffectRenderer->AutoSpriteSizeOn();
	BossEffectRenderer->LeftFlip();
	BossEffectRenderer->Transform.SetLocalPosition({ -560.0f, 14.0f });
	BossEffectRenderer->CreateAnimation("BossLaser", "Boss_Laser");
	BossEffectRenderer->ChangeAnimation("BossLaser");

}

void Boss::Update(float _Delta)
{
}
