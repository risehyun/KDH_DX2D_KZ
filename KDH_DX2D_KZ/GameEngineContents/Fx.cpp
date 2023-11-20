#include "PreCompile.h"
#include "Fx.h"

#define RESOURCE_FX_EXPLOSION "spr_explosion_1"
#define RESOURCE_FX_LANDCLOUD "spr_player_landcloud"
#define RESOURCE_FX_JUMPCLOUD "spr_player_jumpcloud"
#define RESOURCE_FX_DUSTCLOUD "spr_player_dustcloud"

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

	if (Dir != float4::ZERO && GetLiveTime() < 0.5f)
	{
		Transform.AddLocalPosition(Dir * _Delta * Speed);
	}
}

void Fx::SetFxData(EFx_Type _Type, float4 _Dir)
{
	FxType = _Type;
	Dir = _Dir;

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

	case EFx_Type::JumpCloud:
		FxName = RESOURCE_FX_JUMPCLOUD;
		FxRenderer->CreateAnimation("JumpCloud", FxName, 0.1f, 0, 3, false);
		FxRenderer->ChangeAnimation("JumpCloud");
		break;

	case EFx_Type::DustCloud:
		FxName = RESOURCE_FX_DUSTCLOUD;
		FxRenderer->CreateAnimation("DustCloud", FxName, 0.1f, 0, 6, true);
		FxRenderer->ChangeAnimation("DustCloud");
		break;

	case EFx_Type::Default:
	default:
		break;
	}


}