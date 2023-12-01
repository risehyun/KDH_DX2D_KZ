#include "PreCompile.h"
#include "Fx_BossSmokeGroup.h"

Fx_BossSmokeGroup::Fx_BossSmokeGroup()
{
}

Fx_BossSmokeGroup::~Fx_BossSmokeGroup()
{
}

void Fx_BossSmokeGroup::CreateSmokeGroup(float4 _InitFxPos)
{
	InitFxPos = _InitFxPos;

	//기준점 = 약 600
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::StomperCloud, float4::ZERO);

		// 580
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 30.0f, -530.0f });
		NewFx->GetFxRenderer()->LeftFlip();
	}

	// 640
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::StomperCloud, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 30.0f, -530.0f });
	}


	// 스파크
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 80.0f, -530.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 115.0f, -520.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 20.0f });
	}

	// 3번 (5개)
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 55.0f, -500.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 80.0f, -480.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 105.0f, -460.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 130.0f, -480.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	// 2번
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 20.0f, -500.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 25.0f, -470.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 30.0f, -440.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X + 35.0f, -410.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
	}

	//

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 50.0f, -480.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 110.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 30.0f, -450.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	}

	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 30.0f, -380.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	}

	//
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 100.0f, -500.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 150.0f });
	}

	//
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 120.0f, -560.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 180.0f });
	}

	//
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 170.0f, -530.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 165.0f });
	}

	//
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 150.0f, -500.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 170.0f });
	}

	//
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 120.0f, -470.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 110.0f });
	}

	//
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 160.0f, -430.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 130.0f });
	}

	//
	{
		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
		NewFx->Transform.SetLocalPosition({ InitFxPos.X - 120.0f, -400.0f });
		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 120.0f });
	}



}

void Fx_BossSmokeGroup::Start()
{

	// 크기 조절 필요
	//{
	//	std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
	//	NewFx->SetFxData(EFx_Type::GunSmoke, float4::ZERO);
	//	NewFx->Transform.SetLocalPosition({ 640.0f, -530.0f });
	//}

//
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::StomperCloud, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 580.0f, -530.0f });
//		NewFx->GetFxRenderer()->LeftFlip();
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::StomperCloud, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 640.0f, -530.0f });
//	}
//
//
//#pragma region Spark 생성
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 690.0f, -530.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 715.0f, -520.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 20.0f });
//	}
//
//
//	// 3번 (5개)
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 655.0f, -500.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 680.0f, -480.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 705.0f, -460.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 730.0f, -480.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
//	}
//
//
//	// 2번
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 620.0f, -500.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 625.0f, -470.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 630.0f, -440.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 635.0f, -410.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 80.0f });
//	}
//
//	//
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 550.0f, -480.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 110.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 570.0f, -450.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
//	}
//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 570.0f, -380.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
//	}
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 500.0f, -500.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 150.0f });
//	}
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 480.0f, -560.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 180.0f });
//	}
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 430.0f, -530.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 165.0f });
//	}
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 450.0f, -500.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 170.0f });
//	}
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 480.0f, -470.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 110.0f });
//	}
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 440.0f, -430.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 130.0f });
//	}
//
//	//
//	{
//		std::shared_ptr<Fx> NewFx = GetLevel()->CreateActor<Fx>();
//		NewFx->SetFxData(EFx_Type::GunSpark, float4::ZERO);
//		NewFx->Transform.SetLocalPosition({ 480.0f, -400.0f });
//		NewFx->Transform.SetLocalRotation({ 0.0f, 0.0f, 120.0f });
//	}
//
//#pragma endregion
//
//
//


}

void Fx_BossSmokeGroup::Update(float _Delta)
{


}
