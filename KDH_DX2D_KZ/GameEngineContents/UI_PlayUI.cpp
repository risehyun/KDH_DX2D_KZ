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


		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_PresentsText.png"));
			GameEngineSprite::CreateSingle("UI_PresentsText.png");
		}


		//{
		//	GameEngineTexture::Load(FilePath.PlusFilePath("UI_PressAD_0.png"));
		//	GameEngineSprite::CreateSingle("UI_PressAD_0.png");
		//}
	}

	UIRenderer_LeftClick = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_LeftClick->SetSprite("batch_spr_left_click_1.png");
	UIRenderer_LeftClick->AutoSpriteSizeOn();
	UIRenderer_LeftClick->Off();

	UIRenderer_LeftClick->Transform.SetLocalPosition({ 650.f, 450.f, 0.f, 1.0f });

	UIRenderer_PresentText = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_PresentText->SetSprite("UI_PresentsText.png");
	UIRenderer_PresentText->AutoSpriteSizeOn();
	UIRenderer_PresentText->Transform.SetLocalPosition({ 1040.f, 10.f, 0.f, 1.0f });

	Renderer_PressKeyboard = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer_PressKeyboard->CreateAnimation("PressKeyboardAD", "spr_press_keyboard_ad", 0.3f, 0, 1);
	Renderer_PressKeyboard->CreateAnimation("PressKeyboardW", "spr_press_keyboard_w", 0.3f, 0, 1);
	Renderer_PressKeyboard->ChangeAnimation("PressKeyboardAD");
	Renderer_PressKeyboard->AutoSpriteSizeOn();

	Renderer_PressKeyboard->Off();

}

void UI_PlayUI::Update(float _Delta)
{
	if (GetLiveTime() > 2.5f)
	{
		UIRenderer_PresentText->Off();
	}


}