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
	if (nullptr == GameEngineSound::FindSound("song_youwillneverknow.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_youwillneverknow.ogg"));
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
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_MainLevel1_Origin.png", "Map_MainLevel1.png");
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel1.png");


	BGMPlayer = GameEngineSound::SoundPlay("song_youwillneverknow.ogg", 5);
}

void MainLevel1_1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}