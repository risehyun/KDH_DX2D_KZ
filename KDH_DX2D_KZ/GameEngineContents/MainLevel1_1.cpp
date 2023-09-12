#include "PreCompile.h"
#include "MainLevel1_1.h"
#include "Player.h"
#include "SkyMap.h"

#include "Enemy.h"
#include "Door.h"
#include "Portal.h"

#include "Map.h"



MainLevel1_1::MainLevel1_1()
{
}

MainLevel1_1::~MainLevel1_1()
{
}

void MainLevel1_1::Start()
{
	if (nullptr == GameEngineSound::FindSound("song_silhouette.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_silhouette.ogg"));
	}
}

void MainLevel1_1::Update(float _Delta)
{
	//if (true == GameEngineInput::IsDown(VK_RIGHT))
	//{
	//	MapObject->SwitchingRender();
	//}
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
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 150.0f, -HalfWindowScale.Y + 90.0f });
	}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_MainLevel1_Origin.png", "Map_MainLevel1.png");
	}

	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4390.0f, -HalfWindowScale.Y - 250.0f });
	}

	{
		std::shared_ptr<Portal> PortalObject = CreateActor<Portal>();
		PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4500.0f, -HalfWindowScale.Y - 250.0f });
		PortalObject->InitPortalData("TitleLevel", false);
	}

	

	{
	//	CreateActor<SkyMap>();	
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel1.png");

	BGMPlayer.SetVolume(0.3f);
	BGMPlayer = GameEngineSound::SoundPlay("song_silhouette.ogg", 5);
}

void MainLevel1_1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}