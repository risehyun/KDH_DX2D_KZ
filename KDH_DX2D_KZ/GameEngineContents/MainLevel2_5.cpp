#include "PreCompile.h"
#include "MainLevel2_5.h"

MainLevel2_5::MainLevel2_5()
{
}

MainLevel2_5::~MainLevel2_5()
{
}

void MainLevel2_5::Start()
{
}

void MainLevel2_5::Update(float _Delta)
{
	//if (GameEngineInput::IsDown('P'))
	//{
	//	GameEngineCore::ChangeLevel("MainLevel3_1");
	//}
}

void MainLevel2_5::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	//{
	//	std::shared_ptr<Player> Object = CreateActor<Player>();
	//	Object->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y + 150.0f });
	//}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitMap("Map_MainLevel2_5_Origin.png");
	}

	//{
	//	std::shared_ptr<Portal> PortalObject = CreateActor<Portal>();
	//	PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4500.0f, -HalfWindowScale.Y - 250.0f });
	//	PortalObject->InitPortalData("TitleLevel", false);
	//}

	{
		//	CreateActor<SkyMap>();	
	}

	//Player::MainPlayer->SetMapTexture("Map_MainLevel1.png");

	BGMPlayer.SetVolume(0.3f);
	BGMPlayer = GameEngineSound::SoundPlay("song_silhouette.ogg", 5);
}

void MainLevel2_5::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}
