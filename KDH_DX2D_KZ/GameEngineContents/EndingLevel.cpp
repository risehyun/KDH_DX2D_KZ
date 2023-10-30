#include "PreCompile.h"
#include "EndingLevel.h"

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	BaseLevel::InitCameraSetting();

	GameEngineInput::AddInputObject(this);

	{
		MapObject = CreateActor<Map>();
		MapObject->InitMap("spr_ending_dragon_bg.png");
	}

	// Sound Setting
	if (nullptr == GameEngineSound::FindSound("song_ending_2.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_ending_2.ogg"));
	}
}

void EndingLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		DestroyWindow(GameEngineCore::MainWindow.GetHWND());
	}
}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineInput::AddInputObject(this);

	BGMPlayer = GameEngineSound::SoundPlay("song_ending_2.ogg", 5);
	BGMPlayer.SetVolume(0.3f);
}

void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}