#include "PreCompile.h"
#include "MainLevel1_1.h"
#include "Player.h"
#include "SkyMap.h"

#include "Enemy.h"
#include "Door.h"
#include "Portal.h"

#include "PinPointLight.h"

#include "Map.h"

#include "UI_Mouse.h"
#include "UI_PlayUI.h"
#include "UI_FadeObject.h"


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
	if (GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainLevel2_1");
	}


	if (GameEngineInput::IsDown(VK_F1))
	{
		if (true == IsDebug)
		{
			OffDebug();
		}
		else
		{
			OnDebug();
		}
		
	}
}

void MainLevel1_1::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ HalfWindowScale.X, 300, -500.0f });

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y + 150.0f });
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
		PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4725.0f, -HalfWindowScale.Y - 250.0f });
		PortalObject->InitPortalData("MainLevel2_1", true);
	}


	{
		CreateActor<SkyMap>();
	}

	//{
	//	std::shared_ptr<PinPointLight> LightObject = CreateActor<PinPointLight>();
	//	LightObject->Transform.SetLocalPosition({ HalfWindowScale.X - 150.0f, -HalfWindowScale.Y + 90.0f });
	//}





	{
		std::shared_ptr<UI_Mouse> CursorObject = CreateActor<UI_Mouse>();
	}

	
	{
		std::shared_ptr<UI_PlayUI> PlayUIObject = CreateActor<UI_PlayUI>();
	}

	{
		std::shared_ptr<UI_FadeObject> FadeObject = CreateActor<UI_FadeObject>();
	}

	




	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->SetEnemyData(EnemyType::NormalGangster);
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 150.0f, -HalfWindowScale.Y + 90.0f });
		EnemyObject->SetMapTexture("Map_MainLevel1.png");
	}


	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->SetEnemyData(EnemyType::ColoredGangster);
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 300.0f, -HalfWindowScale.Y + 300.0f });
		EnemyObject->SetMapTexture("Map_MainLevel1.png");
	}


	Player::MainPlayer->SetMapTexture("Map_MainLevel1.png");

	BGMPlayer.SetVolume(0.3f);
	BGMPlayer = GameEngineSound::SoundPlay("song_silhouette.ogg", 5);
}

void MainLevel1_1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}