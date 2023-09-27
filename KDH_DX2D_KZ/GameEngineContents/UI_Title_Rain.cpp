#include "PreCompile.h"
#include "UI_Title_Rain.h"

UI_Title_Rain::UI_Title_Rain()
{
}

UI_Title_Rain::~UI_Title_Rain()
{
}

void UI_Title_Rain::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Title\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_rainmask.png"));
			GameEngineSprite::CreateSingle("spr_rainmask.png");
		}
	}

	RainRenderer = CreateComponent<GameEngineUIRenderer>(200);
	RainRenderer->SetSprite("spr_rainmask.png");
	RainRenderer->SetImageScale({ 100, 4 });
	RainRenderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 90.0f, 0.0f });


	RainDeathPos = GameEngineCore::MainWindow.GetScale().Y;

}

void UI_Title_Rain::Update(float _Delta)
{
	RainRenderer->Transform.AddLocalPosition({ 0, float4::DOWN.Y * _Delta * 2500.0f });

	if (RainRenderer->Transform.GetWorldPosition().Y > RainDeathPos)
	{
		Death();
	}
}