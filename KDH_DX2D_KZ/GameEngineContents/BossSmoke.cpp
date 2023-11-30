#include "PreCompile.h"
#include "BossSmoke.h"
#include "Fx.h"
#include "Player.h"

BossSmoke::BossSmoke()
{
}

BossSmoke::~BossSmoke()
{
}

void BossSmoke::Start()
{
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::StomperCloud, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ 640.0f, -530.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::StomperCloud, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ 580.0f, -530.0f });
		NewFx->GetFxRenderer()->LeftFlip();
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ 580.0f, -600.0f });
		NewFx->GetFxRenderer()->LeftFlip();
	}

}

void BossSmoke::Update(float _Delta)
{
}
