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

// ī�޶� �� ũ�� �̻� �Ѿ�� ������ �����ϸ鼭 �÷��̾ �������� ī�޶� �����Դϴ�.
void BaseLevel::CameraFocus(float _Delta)
{
	// ���� �÷��̾�� �Ҵ�� ������ �� �ؽ�ó
	float4 MapScale = Player::MainPlayer->MapTexture->GetScale();

	// ī�޶� ������ ���� �� �������� ���ݿ��� ���� ������ ũ���� ������ �� ũ�⸦ ���մϴ�.
	float4 ClampScale = MapScale / 2.0f - GameEngineCore::MainWindow.GetScale().Half();


	// �� ������ ������ �Ǵ� �ִ��ּ� ������ ���մϴ�.
	// �߽���
	CamPosLimit_Midle = { MapScale.X / 2.0f, -MapScale.Y / 2.0f };

	// ���� �ֻ��
	CamPosLimit_Max = { CamPosLimit_Midle.X - ClampScale.X, CamPosLimit_Midle.Y + ClampScale.Y };

	// ���� ���ϴ�
	CamPosLimit_Min = { CamPosLimit_Midle.X + ClampScale.X, CamPosLimit_Midle.Y - ClampScale.Y };

	CamCurrentPos = GetMainCamera()->Transform.GetWorldPosition();
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();

	// ī�޶� �̵��� �������� �־� ������ �̵��ϵ��� �մϴ�.
	// �̶� �ε巯�� �̵��� ���ؼ� ��ŸŸ���� ���� �� �ణ�� ����ġ�� ���մϴ�.
	// ����ġ�� �ʹ� �������� �̵� �ӵ��� �������Ƿ� ������ �������־����ϴ�.
	CamNextPos = float4::LerpClamp(CamCurrentPos, PlayerPos, _Delta * 2.0f);

	// ī�޶� �̵��� ���� �̻� �Ѿ�� �ʵ��� 4���⿡ ���� ī�޶� ��ġ ����
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
	// ������ Input ������ ���·� ����
	GameEngineInput::AddInputObject(this);

}

void BaseLevel::Update(float _Delta)
{
//	CameraFocus(_Delta);

	// Level FSM �۵�
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
