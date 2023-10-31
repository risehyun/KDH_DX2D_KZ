#include "PreCompile.h"
#include "FX_Explosion.h"

FX_Explosion::FX_Explosion()
{
}

FX_Explosion::~FX_Explosion()
{
}

void FX_Explosion::Start()
{
	FX_ExplosionRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	FX_ExplosionRenderer->CreateAnimation("Explosion", "spr_explosion_1", 0.1f, 0, 10, false);
	FX_ExplosionRenderer->AutoSpriteSizeOn();
	FX_ExplosionRenderer->ChangeAnimation("Explosion");
}

void FX_Explosion::Update(float _Delta)
{
	if (FX_ExplosionRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}