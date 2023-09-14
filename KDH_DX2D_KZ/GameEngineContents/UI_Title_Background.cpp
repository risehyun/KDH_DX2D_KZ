#include "PreCompile.h"

#include "UI_Title_Background.h"
#include "UI_Title_Rain.h"

UI_Title_Background::UI_Title_Background()
{
}

UI_Title_Background::~UI_Title_Background()
{
}

void UI_Title_Background::Start()
{


	if (nullptr == GameEngineSound::FindSound("sound_object_neon_flicker_06.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_object_neon_flicker_06.mp3"));
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Title\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_title_background.png"));
			GameEngineSprite::CreateSingle("spr_title_background.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_title_fence_resize.png"));
			GameEngineSprite::CreateSingle("spr_title_fence_resize.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_titlegraphic_big2.png"));
			GameEngineSprite::CreateSingle("spr_titlegraphic_big2.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_title_grass.png"));
			GameEngineSprite::CreateSingle("spr_title_grass.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_Btn_Title1.png"));
			GameEngineSprite::CreateSingle("UI_Btn_Title1.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("ZeroText.png"));
			GameEngineSprite::CreateSingle("ZeroText.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_title_button_background.png"));
			GameEngineSprite::CreateSingle("spr_title_button_background.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_title_button_select.png"));
			GameEngineSprite::CreateSingle("spr_title_button_select.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_title_buttongroup.png"));
			GameEngineSprite::CreateSingle("spr_title_buttongroup.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_rainmask.png"));
			GameEngineSprite::CreateSingle("spr_rainmask.png");
		}
	}

	std::shared_ptr<GameEngineTexture> BackGroundTex = GameEngineTexture::Find("spr_title_background.png");
	std::shared_ptr<GameEngineTexture> BackGroundFenceTex = GameEngineTexture::Find("spr_title_fence_resize.png");
	std::shared_ptr<GameEngineTexture> TitleTextTex = GameEngineTexture::Find("spr_titlegraphic_big2.png");
	std::shared_ptr<GameEngineTexture> GrassTex = GameEngineTexture::Find("spr_title_grass.png");
	std::shared_ptr<GameEngineTexture> ZeroTextTex = GameEngineTexture::Find("ZeroText.png");



	// ¹öÆ°
	std::shared_ptr<GameEngineSpriteRenderer> Btn_BackgroundRenderer = CreateComponent<GameEngineSpriteRenderer>(200);
	Btn_BackgroundRenderer->SetSprite("spr_title_button_background.png");
	Btn_BackgroundRenderer->SetImageScale({ 550, 250 });
	Btn_BackgroundRenderer->Transform.SetLocalPosition({ 630, -530 });

	std::shared_ptr<GameEngineSpriteRenderer> Btn_SelecterRenderer = CreateComponent<GameEngineSpriteRenderer>(200);
	Btn_SelecterRenderer->SetSprite("spr_title_button_select.png");
	Btn_SelecterRenderer->AutoSpriteSizeOn();
	Btn_SelecterRenderer->Transform.SetLocalPosition({ 630, -445 });

	std::shared_ptr<GameEngineSpriteRenderer> Btn_ButtonGroupRenderer = CreateComponent<GameEngineSpriteRenderer>(200);
	Btn_ButtonGroupRenderer->SetSprite("spr_title_buttongroup.png");
	Btn_ButtonGroupRenderer->SetImageScale({ 550, 250 });
	Btn_ButtonGroupRenderer->Transform.SetLocalPosition({ 630, -530 });








	std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	Renderer->SetSprite("spr_title_background.png");
	Renderer->SetImageScale({ BackGroundTex->GetScale().X * 2.0f, BackGroundTex->GetScale().Y * 2.0f });
	Renderer->Transform.SetLocalPosition({ 640, 0 });


	std::shared_ptr<GameEngineSpriteRenderer> FenceRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	FenceRenderer->SetSprite("spr_title_fence_resize.png");
	FenceRenderer->SetImageScale({ BackGroundTex->GetScale().X * 2.0f, BackGroundTex->GetScale().Y * 2.0f });
	FenceRenderer->Transform.SetLocalPosition({ 640, 0 });

	std::shared_ptr<GameEngineSpriteRenderer> TextRenderer = CreateComponent<GameEngineSpriteRenderer>(100);
	TextRenderer->SetSprite("spr_titlegraphic_big2.png");
	TextRenderer->SetImageScale({ TitleTextTex->GetScale().X * 1.4f, TitleTextTex->GetScale().Y * 1.4f });
	TextRenderer->Transform.SetLocalPosition({ 640, -240 });



	std::shared_ptr<GameEngineSpriteRenderer> PlantRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	PlantRenderer->CreateAnimation("plant", "spr_title_plants");
	PlantRenderer->ChangeAnimation("plant");
	PlantRenderer->Transform.SetLocalPosition({ 640, -500 });

	PlantRenderer->SetImageScale({ 640 * 2.0f, 225 * 2.0f });
	PlantRenderer->SetAutoScaleRatio(0.4f);

	std::shared_ptr<GameEngineSpriteRenderer> GrassRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	GrassRenderer->SetSprite("spr_title_grass.png");
	GrassRenderer->SetImageScale({ GrassTex->GetScale().X * 1.4f, GrassTex->GetScale().Y * 1.4f });
	GrassRenderer->Transform.SetLocalPosition({ 640, -640 });

	std::shared_ptr<GameEngineSpriteRenderer> GameTitleRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	GameTitleRenderer->CreateAnimation("title", "title_zer", 0.001f);
	GameTitleRenderer->ChangeAnimation("title");
	GameTitleRenderer->SetImageScale({ ZeroTextTex->GetScale().X * 0.9f, ZeroTextTex->GetScale().Y * 1.2f });
	GameTitleRenderer->Transform.SetLocalPosition({ 580, -300 });

	std::shared_ptr<GameEngineSpriteRenderer> GameTitleRenderer2 = CreateComponent<GameEngineSpriteRenderer>(-100);
	GameTitleRenderer2->CreateAnimation("title2", "title_o", 1.0f);
	GameTitleRenderer2->ChangeAnimation("title2");
	GameTitleRenderer2->SetImageScale({ ZeroTextTex->GetScale().X * 0.35f, ZeroTextTex->GetScale().Y * 1.2f });
	GameTitleRenderer2->Transform.SetLocalPosition({ 775, -300 });
	GameTitleRenderer2->SetFrameEvent("title2", 4, std::bind(&UI_Title_Background::NeonSoundEvent, this, std::placeholders::_1));

	RainRenderer = CreateComponent<GameEngineSpriteRenderer>(200);
	RainRenderer->SetSprite("spr_rainmask.png");
	RainRenderer->SetImageScale({ 100, 4 });
	RainRenderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 90.0f, 0.0f });
	RainRenderer->Transform.SetLocalPosition({ 630, 0 });

}

void UI_Title_Background::Update(float _Delta)
{
	GameEngineRandom Random;

	RainCreateTimer += _Delta;

	if (RainCreateTimer > 0.3f)
	{
		for (size_t i = 0; i < 8; i++)
		{
			float RainPosX = Random.RandomFloat(0, 1200);
			float RainPosY = Random.RandomFloat(0, 400);

			std::shared_ptr<UI_Title_Rain> TitleRain = CreateComponent<UI_Title_Rain>();
			TitleRain->Transform.SetLocalPosition({ RainPosX, RainPosY });

		}

		RainCreateTimer = 0.f;
	}
}

void UI_Title_Background::NeonSoundEvent(GameEngineRenderer* _Renderer)
{
	BGMPlayer.SetVolume(0.3);
	BGMPlayer = GameEngineSound::SoundPlay("sound_object_neon_flicker_06.mp3", 1);
}

