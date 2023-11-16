#include "PreCompile.h"
#include "Fx.h"

#define RESOURCE_FX_EXPLOSION "spr_explosion_1";
#define RESOURCE_FX_LANDCLOUD "spr_player_landcloud";

Fx::Fx()
{
}

Fx::~Fx()
{
}

void Fx::Start()
{
	FxRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	FxRenderer->AutoSpriteSizeOn();
}

void Fx::Update(float _Delta)
{
	if (true == FxRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void Fx::SetFxData(EFx_Type _Type)
{
	FxType = _Type;

	switch (FxType)
	{
	case EFx_Type::Explosion:
		FxName = RESOURCE_FX_EXPLOSION;
		FxRenderer->CreateAnimation("Explosion", FxName);
		FxRenderer->ChangeAnimation("Explosion");
		break;

	case EFx_Type::LandCloud:
		FxName = RESOURCE_FX_LANDCLOUD;
		FxRenderer->CreateAnimation("LandCloud", FxName, 0.1f, 0, 6, false);
		FxRenderer->ChangeAnimation("LandCloud");
		break;

	case EFx_Type::Default:
	default:
		break;
	}


}