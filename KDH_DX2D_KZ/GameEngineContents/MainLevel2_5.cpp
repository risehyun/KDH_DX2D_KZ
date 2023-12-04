#include "PreCompile.h"
#include "MainLevel2_5.h"
#include "Player.h"
#include "UI_Mouse.h"

MainLevel2_5::MainLevel2_5()
{
}

MainLevel2_5::~MainLevel2_5()
{
}

void MainLevel2_5::Start()
{

#pragma region 레벨 효과음 로딩

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\FX\\LevelFX\\");

		if (nullptr == GameEngineSound::FindSound("sound_slomo_disengage.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_disengage.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_slomo_engage.ogg"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_engage.ogg"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_rewind.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_rewind.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_level_start.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_level_start.wav"));
		}
	}

#pragma endregion


	GameEngineInput::AddInputObject(this);

	BaseLevel::InitCameraSetting();

	//FSM_Level_PlayGame();
	//FSM_Level_SlowGame();
	//FSM_Level_InitGame();
	//FSM_Level_ReplayGame();
	//FSM_Level_ReverseGame();

}

void MainLevel2_5::Update(float _Delta)
{

	CameraFocus(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("BossLevel1_2");
	}

//	LevelState.Update(_Delta);

}

void MainLevel2_5::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);




	{
		MapObject = CreateActor<Map>();

		MapObject->InitDebuggedMap("Map_MainLevel2_5_Origin.png", "Map_MainLevel2_5.png");
	}


	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 400.0f, -HalfWindowScale.Y + 150.0f });
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel2_5.png");


	{
		std::shared_ptr<UI_Mouse> Object = CreateActor<UI_Mouse>();
	}

	if (nullptr == GameEngineSound::FindSound("song_dragon.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_dragon.ogg"));
	}

	BGMPlayer = GameEngineSound::SoundPlay("song_dragon.ogg", 5);
	BGMPlayer.SetVolume(0.3f);

//	LevelState.ChangeState(LevelState::InitGame);

}

void MainLevel2_5::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}