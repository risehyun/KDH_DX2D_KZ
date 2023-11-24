#include "PreCompile.h"
#include "BaseLevel.h"
#include "Player.h"
#include "GameStateManager.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

// 카메라가 맵 크기 이상 넘어가는 현상을 방지하면서 플레이어를 기준으로 카메라를 움직입니다.
void BaseLevel::CameraFocus(float _Delta)
{
	// 현재 플레이어에게 할당된 레벨의 맵 텍스처
	float4 MapScale = Player::MainPlayer->MapTexture->GetScale();

	// 카메라 보간을 위해 맵 스케일의 절반에서 현재 윈도우 크기의 절반을 뺀 크기를 구합니다.
	float4 ClampScale = MapScale / 2.0f - GameEngineCore::MainWindow.GetScale().Half();


	// 각 방향의 기준이 되는 최대최소 지점을 구합니다.
	// 중심점
	CamPosLimit_Midle = { MapScale.X / 2.0f, -MapScale.Y / 2.0f };

	// 좌측 최상단
	CamPosLimit_Max = { CamPosLimit_Midle.X - ClampScale.X, CamPosLimit_Midle.Y + ClampScale.Y };

	// 우측 최하단
	CamPosLimit_Min = { CamPosLimit_Midle.X + ClampScale.X, CamPosLimit_Midle.Y - ClampScale.Y };

	CamCurrentPos = GetMainCamera()->Transform.GetWorldPosition();
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();

	// 카메라 이동시 러프값을 주어 서서히 이동하도록 합니다.
	// 이때 부드러운 이동을 위해서 델타타임을 곱할 때 약간의 보정치를 곱합니다.
	// 보정치가 너무 높아지면 이동 속도가 빨라지므로 적당히 조절해주었습니다.
	CamNextPos = float4::LerpClamp(CamCurrentPos, PlayerPos, _Delta * 2.0f);

	// 카메라 이동시 범위 이상 넘어가지 않도록 4방향에 대한 카메라 위치 조정
	if (CamNextPos.X < CamPosLimit_Max.X)
	{
		CamNextPos.X = CamPosLimit_Max.X;
	}

	if (CamNextPos.X > CamPosLimit_Min.X)
	{
		CamNextPos.X = CamPosLimit_Min.X;
	}

	if (CamNextPos.X < CamPosLimit_Max.X)
	{
		CamNextPos.X = CamPosLimit_Max.X;
	}

	if (CamNextPos.Y > CamPosLimit_Max.Y)
	{
		CamNextPos.Y = CamPosLimit_Max.Y;
	}

	if (CamNextPos.Y < CamPosLimit_Min.Y)
	{
		CamNextPos.Y = CamPosLimit_Min.Y;
	}

	GetMainCamera()->Transform.SetWorldPosition(CamNextPos);

}

void BaseLevel::Start()
{
	// 레벨이 Input 가능한 상태로 만듦
	GameEngineInput::AddInputObject(this);

}

void BaseLevel::Update(float _Delta)
{
//	CameraFocus(_Delta);

	// Level FSM 작동
//	LevelState.Update(_Delta);

}

void BaseLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
//	InitCameraSetting();

	{
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}
}

void BaseLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void BaseLevel::InitCameraSetting()
{
//	1280 * 720

//	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	CameraInitPos = { 640.0f, -360.0f, -500.0f };

	GetMainCamera()->Transform.SetLocalPosition(CameraInitPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ 640.0f, 300.0f, -500.0f });
}
