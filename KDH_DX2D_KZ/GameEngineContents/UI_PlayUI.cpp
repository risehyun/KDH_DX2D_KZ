#include "PreCompile.h"
#include "UI_PlayUI.h"
#include "GameStateManager.h"

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

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_go_arrow.png"));
			GameEngineSprite::CreateSingle("spr_go_arrow.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_hud_dragon.png"));
			GameEngineSprite::CreateSingle("spr_hud_dragon.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_GoAll.png"));
			GameEngineSprite::CreateSingle("UI_GoAll.png");
		}
		
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_GameOverText.png"));
			GameEngineSprite::CreateSingle("UI_GameOverText.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_itemicons_0.png"));
			GameEngineSprite::CreateSingle("spr_itemicons_0.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_katanaicons_3.png"));
			GameEngineSprite::CreateSingle("spr_katanaicons_3.png");
		}
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
	UIRenderer_PresentText->Off();

	Renderer_PressKeyboard = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer_PressKeyboard->CreateAnimation("PressKeyboardAD", "spr_press_keyboard_ad", 0.3f, 0, 1);
	Renderer_PressKeyboard->CreateAnimation("PressKeyboardW", "spr_press_keyboard_w", 0.3f, 0, 1);
	Renderer_PressKeyboard->ChangeAnimation("PressKeyboardAD");
	Renderer_PressKeyboard->AutoSpriteSizeOn();
	Renderer_PressKeyboard->Off();

	Renderer_GoArrow = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer_GoArrow->SetSprite("spr_go_arrow.png");
	Renderer_GoArrow->AutoSpriteSizeOn();
	Renderer_GoArrow->Transform.SetLocalPosition({ 4900.f, -620.0f, 0.f, 1.0f });
	Renderer_GoArrow->Off();

	UIRenderer_GoArrow = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_GoArrow->SetSprite("UI_GoAll.png");
	UIRenderer_GoArrow->AutoSpriteSizeOn();
	UIRenderer_GoArrow->Transform.SetLocalPosition({ 1180.0f, 200.0f, 0.f, 1.0f });
	UIRenderer_GoArrow->Off();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	UIRenderer_Hud = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_Hud->SetSprite("spr_hud_dragon.png");
	UIRenderer_Hud->AutoSpriteSizeOn();
	UIRenderer_Hud->Transform.SetLocalPosition({ HalfWindowScale.X, HalfWindowScale.Y + 278.0f, 0.f, 1.0f });
	UIRenderer_Hud->Off();


	///

	UIRenderer_WeaponIcon = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_WeaponIcon->SetSprite("spr_katanaicons_3.png");
	UIRenderer_WeaponIcon->AutoSpriteSizeOn();
	UIRenderer_WeaponIcon->Transform.SetLocalPosition({ HalfWindowScale.X + 530.0f, HalfWindowScale.Y + 278.0f, 0.f, 1.0f });
//	UIRenderer_WeaponIcon->Off();

	// ★ 추후 아이템들이 추가되면 여기에 적용되는 스프라이트가 여러개가 되므로 구조를 변경해야 한다.
	UIRenderer_ItemIcon = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_ItemIcon->SetSprite("spr_itemicons_0.png");
	UIRenderer_ItemIcon->AutoSpriteSizeOn();
	UIRenderer_ItemIcon->Transform.SetLocalPosition({ HalfWindowScale.X + 596.0f, HalfWindowScale.Y + 278.0f, 0.f, 1.0f });
//	UIRenderer_ItemIcon->Off();


	UIRenderer_GameOver = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_GameOver->SetSprite("UI_GameOverText.png");
	UIRenderer_GameOver->AutoSpriteSizeOn();
	UIRenderer_GameOver->Transform.SetLocalPosition({ HalfWindowScale.X, HalfWindowScale.Y, 0.f, 1.0f });
	UIRenderer_GameOver->Off();
}

void UI_PlayUI::Update(float _Delta)
{
	if (true == UIRenderer_PresentText->GetUpdateValue() && GetLiveTime() > 2.5f)
	{
		UIRenderer_PresentText->Off();
	}

	//if (true == GameStateManager::GameState->GetCurrentGameState())
	//{
	//	if (true == UIRenderer_GameOver->GetUpdateValue())
	//	{
	//		return;
	//	}

	//	UIRenderer_GameOver->On();
	//}
	//else
	//{
	//	if (false == UIRenderer_GameOver->GetUpdateValue())
	//	{
	//		return;
	//	}

	//	UIRenderer_GameOver->Off();
	//}

}

void UI_PlayUI::UsePresentText()
{
	UIRenderer_PresentText->On();
}

void UI_PlayUI::UseHUD()
{
	UIRenderer_Hud->On();
}

void UI_PlayUI::OnGameOverUI()
{
	UIRenderer_GameOver->On();
}

void UI_PlayUI::OffGameOverUI()
{
	UIRenderer_GameOver->Off();
}

void UI_PlayUI::OnGoArrow()
{
	UIRenderer_GoArrow->On();
}