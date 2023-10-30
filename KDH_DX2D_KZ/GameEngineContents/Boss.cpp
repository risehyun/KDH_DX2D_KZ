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
//	BossMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);
//	BossMainRenderer->CreateAnimation("Turn", "spr_gangsterturn", 0.2f, 0, 5, false);

	BossMainRenderer->ChangeAnimation("Idle");

}

void Boss::Update(float _Delta)
{
}
