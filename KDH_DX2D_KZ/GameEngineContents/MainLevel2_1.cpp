#include "PreCompile.h"
#include "MainLevel2_1.h"
#include "JobFolder.h"

MainLevel2_1::MainLevel2_1()
{
}

MainLevel2_1::~MainLevel2_1()
{
}

void MainLevel2_1::Start()
{
}

void MainLevel2_1::Update(float _Delta)
{
	if (GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainLevel2_2");
	}

}

void MainLevel2_1::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		MapObject = CreateActor<Map>();
		MapObject->InitMap("spr_black.png");
		MapObject->Transform.SetLocalScale(GameEngineCore::MainWindow.GetScale());
	}

	{
		std::shared_ptr<JobFolder> JobFolderObject = CreateActor<JobFolder>();
	}

	

}

void MainLevel2_1::LevelEnd(GameEngineLevel* _NextLevel)
{
}
