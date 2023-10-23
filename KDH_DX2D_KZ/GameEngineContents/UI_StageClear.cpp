#include "PreCompile.h"
#include "UI_StageClear.h"

UI_StageClear::UI_StageClear()
{
}

UI_StageClear::~UI_StageClear()
{
}

void UI_StageClear::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_YesThatShouldWork.png"));
			GameEngineSprite::CreateSingle("UI_YesThatShouldWork.png");
		}
	}


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	UIRenderer_StageClearText = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_StageClearText->SetSprite("UI_YesThatShouldWork.png");
	UIRenderer_StageClearText->AutoSpriteSizeOn();
	UIRenderer_StageClearText->Transform.SetLocalPosition({ HalfWindowScale.X, HalfWindowScale.Y - 100.0f });

}

void UI_StageClear::Update(float _Delta)
{
}
