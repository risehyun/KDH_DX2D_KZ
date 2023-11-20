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
		CreateRunCloudGroup();
	}
	else if (Type == EFX_DustCloudGroup_Type::RollCloud)
	{
		CreateRollCloudGroup();
	}
}

void FX_DustCloudGroup::Start()
{
	PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();
	PlayerDir = Player::MainPlayer->GetPlayerDir();
}

void FX_DustCloudGroup::Update(float _Delta)
{

	if (true == IsStartRollCloudMove)
	{
		// 다시 플레이어 위치를 실시간으로 갱신
		PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();
		float4 FxGroupPos = Transform.GetLocalPosition();

		float initXPos = 30.0f;
		float initYPos = 0.0f;

		int a = DustCloudGroup.size();

		for (int i = 0; i < DustCloudGroup.size(); i++)
		{
			if (i == 1)
			{
				initYPos = 10.0f;
			}

			else if (i == 2)
			{
				initYPos = -10.0f;
			}

			DustCloudGroup[i]->Transform.SetLocalPosition({ initXPos + PlayerPos.X + (i * 25), initYPos + PlayerPos.Y - 30.0f });
		}

		

	//	CreateRollCloudGroup();

	//	IsStartRollCloudMove = false;



//		Transform.AddLocalPosition(PlayerPos - FxGroupPos);
	}
}

void FX_DustCloudGroup::CreateRunCloudGroup()
{


	// 기준점
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = 40.0f;
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
		PlayerDir = Player::MainPlayer->GetPlayerDir();
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
		PlayerDir = Player::MainPlayer->GetPlayerDir();
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
		PlayerDir = Player::MainPlayer->GetPlayerDir();
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
		PlayerDir = Player::MainPlayer->GetPlayerDir();
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

void FX_DustCloudGroup::CreateRollCloudGroup()
{
	// 기준점
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -10.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -30.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -50.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -70.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -90.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -110.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -130.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::DustCloud, -PlayerDir);

		float XPos = -150.0f;
		float XPosDouble = XPos * 2.0f;

		float4 FxInitPos = { PlayerPos.X + XPos,  PlayerPos.Y - 30.0f };

		DustCloudGroup.push_back(NewFx);

		NewFx->Transform.SetLocalPosition(FxInitPos);
	}

	IsStartRollCloudMove = true;
}
