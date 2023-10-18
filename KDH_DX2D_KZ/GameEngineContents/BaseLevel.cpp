#include "PreCompile.h"
#include "BaseLevel.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::Start()
{
}

void BaseLevel::Update(float _Delta)
{
}

void BaseLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	InitCameraSetting();
}

void BaseLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void BaseLevel::InitCameraSetting()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	CameraInitPos = { HalfWindowScale.X, -HalfWindowScale.Y, -500.0f };

	GetMainCamera()->Transform.SetLocalPosition(CameraInitPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ HalfWindowScale.X, 300, -500.0f });
}