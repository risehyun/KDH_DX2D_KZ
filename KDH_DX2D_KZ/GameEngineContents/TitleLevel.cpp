#include "PreCompile.h"
#include "TitleLevel.h"
#include "UI_Title_Background.h"
#include <GameEngineBase/GameEngineMath.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Texture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

	}

	if (nullptr == GameEngineSound::FindSound("Sound_song_title.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Sound_song_title.ogg"));
	}


	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, 300, -500.0f });

	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	std::shared_ptr<UI_Title_Background> BackGroundObject = CreateActor<UI_Title_Background>();

}

void TitleLevel::Update(float _Delta)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	if (GetMainCamera()->Transform.GetWorldPosition().Y > -(HalfWindowScale.Y))
	{
		GetMainCamera()->Transform.AddLocalPosition({ 0, -500.f * _Delta });
	}


	if (GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("MainLevel1_1");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineSound::SoundPlay("Sound_song_title.ogg", 5);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}