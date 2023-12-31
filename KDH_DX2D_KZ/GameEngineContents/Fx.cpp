#include "PreCompile.h"
#include "Fx.h"

#define RESOURCE_FX_EXPLOSION "spr_explosion_1"
#define RESOURCE_FX_LANDCLOUD "spr_player_landcloud"
#define RESOURCE_FX_JUMPCLOUD "spr_player_jumpcloud"
#define RESOURCE_FX_DUSTCLOUD "spr_player_dustcloud"
#define RESOURCE_FX_STOMPERCLOUD "spr_stompercloud"
#define RESOURCE_FX_GUNSPARK "spr_gunspark3"
#define RESOURCE_FX_GUNSMOKE "spr_gunsmoke3"
#define RESOURCE_FX_BULLETREFLECT "spr_bulletreflect"
#define RESOURCE_FX_SLASH "spr_slashfx"
#define RESOURCE_FX_HITIMPACT "spr_hit_impact"

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
		// 오른쪽에서 왼쪽으로 타격할 때 거꾸로 뒤집어줘야 하고, 이동 방향도 반대가 되어야 한다.
		if (FxType == EFx_Type::HitImpact)
		{
			if (Dir.X < 0.0f)
			{
				FxRenderer->LeftFlip();
			}
			else
			{
				FxRenderer->RightFlip();
			}

			Transform.SetLocalRotation({ 0.0f, 0.0f, Dir.X });

		}
		else
		{
			Transform.AddLocalPosition(Dir * _Delta * Speed);
		}
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
		FxRenderer->CreateAnimation("DustCloud", FxName, 0.1f, 0, 6, false);
		FxRenderer->ChangeAnimation("DustCloud");
		break;

	case EFx_Type::StomperCloud:
		FxName = RESOURCE_FX_STOMPERCLOUD;
		FxRenderer->CreateAnimation("StomperCloud", FxName, 0.1f, 0, 9, false);
		FxRenderer->ChangeAnimation("StomperCloud");
		break;

	case EFx_Type::GunSpark:
		FxName = RESOURCE_FX_GUNSPARK;
		FxRenderer->CreateAnimation("GunSpark", FxName, 0.1f, 0, 7, false);
		FxRenderer->ChangeAnimation("GunSpark");
		break;

	case EFx_Type::GunSmoke:
		FxName = RESOURCE_FX_GUNSMOKE;
		FxRenderer->CreateAnimation("GunSmoke", FxName, 0.1f, 0, 10, false);
		FxRenderer->ChangeAnimation("GunSmoke");
		break;

	case EFx_Type::BulletReflect:
		FxName = RESOURCE_FX_BULLETREFLECT;
		FxRenderer->CreateAnimation("BulletReflect", FxName, 0.1f, 0, 4, false);
		FxRenderer->ChangeAnimation("BulletReflect");
		break;

	case EFx_Type::Slash:
		FxName = RESOURCE_FX_SLASH;
		FxRenderer->CreateAnimation("Slash", FxName, 0.1f, 0, 4, false);
		FxRenderer->ChangeAnimation("Slash");
		break;

	case EFx_Type::HitImpact:
		FxName = RESOURCE_FX_HITIMPACT;
		FxRenderer->CreateAnimation("HitImpact", FxName, 0.1f, 0, 5, false);
		FxRenderer->ChangeAnimation("HitImpact");
		break;

	default:
		break;
	}
}