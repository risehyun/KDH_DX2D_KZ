#include "PreCompile.h"
#include "UI_PlayUI.h"

UI_PlayUI* UI_PlayUI::PlayUI = nullptr;

UI_PlayUI::UI_PlayUI()
{
	PlayUI = this;
}

UI_PlayUI::~UI_PlayUI()
{

}

void UI_PlayUI::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("batch_spr_left_click_1.png"));
			GameEngineSprite::CreateSingle("batch_spr_left_click_1.png");
		}
	}

	UIRenderer = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer->SetSprite("batch_spr_left_click_1.png");
	UIRenderer->AutoSpriteSizeOn();

	UIRenderer->Transform.SetLocalPosition({ 100.f, 100.f, 0.f, 1.0f });
}

void UI_PlayUI::Update(float _Delta)
{

}