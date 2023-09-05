#include "PreCompile.h"
#include "MainLevel1_1.h"
#include "Player.h"
//#include "PlayMap.h"

#include "Map.h"

MainLevel1_1::MainLevel1_1()
{
}

MainLevel1_1::~MainLevel1_1()
{
}

void MainLevel1_1::Start()
{

}

void MainLevel1_1::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		MapObject->SwitchingRender();
	}
}

void MainLevel1_1::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y + 150.0f });
	}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_MainLevel1_Origin.png", "Map_MainLevel1.png");
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel1.png");
}

void MainLevel1_1::LevelEnd(GameEngineLevel* _NextLevel)
{
}