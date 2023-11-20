#include "PreCompile.h"
#include "FX_DustCloudGroup.h"
#include "Player.h"

FX_DustCloudGroup::FX_DustCloudGroup()
{
}

FX_DustCloudGroup::~FX_DustCloudGroup()
{
}

void FX_DustCloudGroup::SetType(EFX_DustCloudGroup_Type _Type)
{
	Type = _Type;

	if (Type == EFX_DustCloudGroup_Type::RunCloud)
	{
		Create_DustCloudGroup();
	}
	else if (Type == EFX_DustCloudGroup_Type::RollCloud)
	{
		IsStartRollCloudCreate = true;
	}
}

void FX_DustCloudGroup::Start()
{
	PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();
	PlayerDir = Player::MainPlayer->GetPlayerDir();
}

void FX_DustCloudGroup::Update(float _Delta)
{
	if (Type == EFX_DustCloudGroup_Type::RollCloud && GetLiveTime() < 0.4f)
	{
		RollCloudCreateTimer += _Delta;

		if (RollCloudCreateTimer > 0.05f)
		{
			Create_RollDustCloudGroup();
		}
	}
}

void FX_DustCloudGroup::Create_DustCloudGroup()
{
	// ±‚¡ÿ¡°
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 20.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		if (float4::RIGHT == PlayerDir)
		{
			NewFx->Transform.SetLocalPosition({ FxInitPos.X - XPosDouble, FxInitPos.Y });
		}
		else
		{
			NewFx->Transform.SetLocalPosition(FxInitPos);
		}
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 30.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos, PlayerPos.Y - 15.0f };

		if (float4::RIGHT == PlayerDir)
		{
			NewFx->Transform.SetLocalPosition({ FxInitPos.X - XPosDouble, FxInitPos.Y });
		}
		else
		{
			NewFx->Transform.SetLocalPosition(FxInitPos);
		}


	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 40.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 40.0f };

		if (float4::RIGHT == PlayerDir)
		{
			NewFx->Transform.SetLocalPosition({ FxInitPos.X - XPosDouble, FxInitPos.Y });
		}
		else
		{
			NewFx->Transform.SetLocalPosition(FxInitPos);
		}
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 50.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		if (float4::RIGHT == PlayerDir)
		{
			NewFx->Transform.SetLocalPosition({ FxInitPos.X - XPosDouble, FxInitPos.Y });
		}
		else
		{
			NewFx->Transform.SetLocalPosition(FxInitPos);
		}
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 60.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 20.0f };

		if (float4::RIGHT == PlayerDir)
		{
			NewFx->Transform.SetLocalPosition({ FxInitPos.X - XPosDouble, FxInitPos.Y });
		}
		else
		{
			NewFx->Transform.SetLocalPosition(FxInitPos);
		}
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 70.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 35.0f };

		if (float4::RIGHT == PlayerDir)
		{
			NewFx->Transform.SetLocalPosition({ FxInitPos.X - XPosDouble, FxInitPos.Y });
		}
		else
		{
			NewFx->Transform.SetLocalPosition(FxInitPos);
		}
	}

}

void FX_DustCloudGroup::Create_RollDustCloudGroup()
{
	PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();
	Create_DustCloudGroup();
	RollCloudCreateTimer = 0.0f;
}
