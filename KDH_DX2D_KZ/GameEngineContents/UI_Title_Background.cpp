#include "PreCompile.h"
#include "UI_Title_Background.h"

UI_Title_Background::UI_Title_Background()
{
}

UI_Title_Background::~UI_Title_Background()
{
}

void UI_Title_Background::Start()
{

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
			GameEngineTexture::Load(FilePath.PlusFilePath("ZeroText.png"));
			GameEngineSprite::CreateSingle("ZeroText.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_Btn_Title1.png"));
			GameEngineSprite::CreateSingle("UI_Btn_Title1.png");
		}
	}

	std::shared_ptr<GameEngineTexture> BackGroundTex = GameEngineTexture::Find("spr_title_background.png");
	std::shared_ptr<GameEngineTexture> BackGroundFenceTex = GameEngineTexture::Find("spr_title_fence_resize.png");
	std::shared_ptr<GameEngineTexture> TitleTextTex = GameEngineTexture::Find("spr_titlegraphic_big2.png");
	std::shared_ptr<GameEngineTexture> GrassTex = GameEngineTexture::Find("spr_title_grass.png");
	std::shared_ptr<GameEngineTexture> ZeroTextTex = GameEngineTexture::Find("ZeroText.png");


	std::shared_ptr<GameEngineTexture> Btn_NewGameTex = GameEngineTexture::Find("UI_Btn_Title1.png");


	std::shared_ptr<GameEngineSpriteRenderer> Btn_NewGameRenderer = CreateComponent<GameEngineSpriteRenderer>(200);
	Btn_NewGameRenderer->SetSprite("UI_Btn_Title1.png");
	Btn_NewGameRenderer->Transform.SetLocalScale({ Btn_NewGameTex->GetScale().X / 2, Btn_NewGameTex->GetScale().Y / 2 });
	Btn_NewGameRenderer->Transform.SetLocalPosition({ 630, -550 });



	std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	Renderer->SetSprite("spr_title_background.png");
	Renderer->Transform.SetLocalScale({ BackGroundTex->GetScale().X * 2.0f, BackGroundTex->GetScale().Y * 2.0f });
	Renderer->Transform.SetLocalPosition({ 640, 0 });


	std::shared_ptr<GameEngineSpriteRenderer> FenceRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	FenceRenderer->SetSprite("spr_title_fence_resize.png");
	FenceRenderer->Transform.SetLocalScale({ BackGroundTex->GetScale().X * 2.0f, BackGroundTex->GetScale().Y * 2.0f });
	FenceRenderer->Transform.SetLocalPosition({ 640, 0 });

	std::shared_ptr<GameEngineSpriteRenderer> TextRenderer = CreateComponent<GameEngineSpriteRenderer>(100);
	TextRenderer->SetSprite("spr_titlegraphic_big2.png");
	TextRenderer->Transform.SetLocalScale({ TitleTextTex->GetScale().X * 1.4f, TitleTextTex->GetScale().Y * 1.4f });
	TextRenderer->Transform.SetLocalPosition({ 640, -240 });



	std::shared_ptr<GameEngineSpriteRenderer> PlantRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	PlantRenderer->CreateAnimation("plant", "spr_title_plants");
	PlantRenderer->ChangeAnimation("plant");
	PlantRenderer->Transform.SetLocalPosition({ 640, -500 });

	PlantRenderer->Transform.SetLocalScale({ 640 * 2.0f, 225 * 2.0f });
	//	MainSpriteRenderer->AutoSpriteSizeOn();
	PlantRenderer->SetAutoScaleRatio(0.4f);

	std::shared_ptr<GameEngineSpriteRenderer> GrassRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	GrassRenderer->SetSprite("spr_title_grass.png");
	GrassRenderer->Transform.SetLocalScale({ GrassTex->GetScale().X * 1.4f, GrassTex->GetScale().Y * 1.4f });
	GrassRenderer->Transform.SetLocalPosition({ 640, -640 });


	std::shared_ptr<GameEngineSpriteRenderer> ZeroTextRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	ZeroTextRenderer->SetSprite("ZeroText.png");
	ZeroTextRenderer->Transform.SetLocalScale({ ZeroTextTex->GetScale().X * 1.2f, ZeroTextTex->GetScale().Y * 1.2f });
	ZeroTextRenderer->Transform.SetLocalPosition({ 640, -300 });

}