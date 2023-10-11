#include "PreCompile.h"
#include "UI_NowPlayingSong.h"

UI_NowPlayingSong::UI_NowPlayingSong()
{
}

UI_NowPlayingSong::~UI_NowPlayingSong()
{
}

void UI_NowPlayingSong::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_songtitleBackGround.png"));
			GameEngineSprite::CreateSingle("spr_songtitleBackGround.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("Nowplayingsong_All.png"));
			GameEngineSprite::CreateSingle("Nowplayingsong_All.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_songunderline.png"));
			GameEngineSprite::CreateSingle("spr_songunderline.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("Nowplayingsong_Cyan.png"));
			GameEngineSprite::CreateSingle("Nowplayingsong_Cyan.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("Nowplayingsong_Magenta.png"));
			GameEngineSprite::CreateSingle("Nowplayingsong_Magenta.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("SongTitle.png"));
			GameEngineSprite::CreateSingle("SongTitle.png");
		}
	
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();


	UIRenderer_SongTitleBackGround = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_SongTitleBackGround->SetSprite("spr_songtitleBackGround.png");
	UIRenderer_SongTitleBackGround->AutoSpriteSizeOn();
	UIRenderer_SongTitleBackGround->Transform.SetLocalPosition({ HalfWindowScale.X - 430.0f, HalfWindowScale.Y - 350.0f });
	//	UIRenderer_SongTitleBackGround->Off();


	UIRenderer_NowPlayingText_Cyan = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_NowPlayingText_Cyan->SetSprite("Nowplayingsong_Cyan.png");
	UIRenderer_NowPlayingText_Cyan->AutoSpriteSizeOn();
	UIRenderer_NowPlayingText_Cyan->Transform.SetLocalPosition({ HalfWindowScale.X - 440.0f, HalfWindowScale.Y - 350.0f });
	//	UIRenderer_NowPlayingText_Cyan->Off();



	UIRenderer_NowPlayingText_Magenta = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_NowPlayingText_Magenta->SetSprite("Nowplayingsong_Magenta.png");
	UIRenderer_NowPlayingText_Magenta->AutoSpriteSizeOn();
	UIRenderer_NowPlayingText_Magenta->Transform.SetLocalPosition({ HalfWindowScale.X - 420.0f, HalfWindowScale.Y - 350.0f });
	//	UIRenderer_NowPlayingText_Magenta->Off();



	UIRenderer_NowPlayingText_All = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_NowPlayingText_All->SetSprite("Nowplayingsong_All.png");
	UIRenderer_NowPlayingText_All->AutoSpriteSizeOn();
	UIRenderer_NowPlayingText_All->Transform.SetLocalPosition({ HalfWindowScale.X - 430.0f, HalfWindowScale.Y - 350.0f });
	UIRenderer_NowPlayingText_All->Off();

	UIRenderer_SongTitleLine = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_SongTitleLine->SetSprite("spr_songunderline.png");
	UIRenderer_SongTitleLine->AutoSpriteSizeOn();
	UIRenderer_SongTitleLine->Transform.SetLocalPosition({ HalfWindowScale.X - 430.0f, HalfWindowScale.Y - 350.0f });
	//	UIRenderer_SongTitleLine->Off();

	UIRenderer_SongTitle = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_SongTitle->SetSprite("SongTitle.png");
	UIRenderer_SongTitle->AutoSpriteSizeOn();
	UIRenderer_SongTitle->Transform.SetLocalPosition({ HalfWindowScale.X - 430.0f, HalfWindowScale.Y - 350.0f });
	//	UIRenderer_SongTitle->Off();

}

void UI_NowPlayingSong::Update(float _Delta)
{
	float4 CyanRendererPos = UIRenderer_NowPlayingText_Cyan->Transform.GetWorldPosition();
	float4 MagentaRendererPos = UIRenderer_NowPlayingText_Magenta->Transform.GetWorldPosition();

	float4 TargetPos = UIRenderer_NowPlayingText_All->Transform.GetWorldPosition();

	if (CyanRendererPos.X < TargetPos.X)
	{
		UIRenderer_NowPlayingText_Cyan->Transform.AddWorldPosition({ 10.0f * _Delta * 10.0f, 0.0f });
	}

	if (MagentaRendererPos.X > TargetPos.X)
	{
		UIRenderer_NowPlayingText_Magenta->Transform.AddWorldPosition({ -10.0f * _Delta * 10.0f, 0.0f });
	}

	if (CyanRendererPos.X > TargetPos.X && MagentaRendererPos.X < TargetPos.X)
	{
		UIRenderer_NowPlayingText_Cyan->Off();
		UIRenderer_NowPlayingText_Magenta->Off();
		UIRenderer_NowPlayingText_All->On();
	}

	if (GetLiveTime() > 3.0f)
	{
		Death();
	}
}
