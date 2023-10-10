#include "PreCompile.h"
#include "MainLevel2_2.h"
#include "Player.h"
#include "SkyMap.h"
#include "Portal.h"
#include "UI_StageName.h"

MainLevel2_2::MainLevel2_2()
{
}

MainLevel2_2::~MainLevel2_2()
{
}

void MainLevel2_2::Start()
{
}

void MainLevel2_2::Update(float _Delta)
{
	if (GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainLevel2_3");
	}
}

void MainLevel2_2::LevelStart(GameEngineLevel* _PrevLevel)
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
		MapObject->InitDebuggedMap("Map_MainLevel2_2_Origin.png", "Map_MainLevel2_2.png");
	}

	{
		std::shared_ptr<Portal> PortalObject = CreateActor<Portal>();
		PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 2500.0f, -HalfWindowScale.Y-200.0f });
		PortalObject->InitPortalData("MainLevel2_3", false);
	}

	{
		std::shared_ptr<SkyMap> SkyMapObject = CreateActor<SkyMap>();
		SkyMapObject->SetSkyMapType(ESkyType::PrisonSky);
	}

	{
		PlayUIObject = CreateActor<UI_PlayUI>();
	}

	{
		std::shared_ptr<UI_StageName> StageNameObejct = CreateActor<UI_StageName>();
		StageNameObejct->InitStageNameData(EStageNameType::Prison);
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel2_2.png");

	BGMPlayer.SetVolume(0.3f);
	BGMPlayer = GameEngineSound::SoundPlay("song_silhouette.ogg", 5);

}

void MainLevel2_2::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}
