#include "PreCompile.h"
#include "FX_DustCloudGroup.h"
#include "Player.h"

FX_DustCloudGroup::FX_DustCloudGroup()
{
}

FX_DustCloudGroup::~FX_DustCloudGroup()
{
}

void FX_DustCloudGroup::Start()
{

	float4 PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();

	// ±‚¡ÿ¡°
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		float4 PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 40.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		if (float4::RIGHT == PlayerDir)
		{
			NewFx->Transform.SetLocalPosition({ FxInitPos.X - XPosDouble, FxInitPos.Y});
		}
		else
		{
			NewFx->Transform.SetLocalPosition(FxInitPos);
		}
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		float4 PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 50.0f;
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
		float4 PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 60.0f;
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
		float4 PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 70.0f;
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
		float4 PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 80.0f;
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
		float4 PlayerDir = Player::MainPlayer->GetPlayerDir();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 90.0f;
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

void FX_DustCloudGroup::Update(float _Delta)
{
}
