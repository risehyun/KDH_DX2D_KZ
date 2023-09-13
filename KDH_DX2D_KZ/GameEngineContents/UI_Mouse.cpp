#include "PreCompile.h"
#include "UI_Mouse.h"

UI_Mouse::UI_Mouse()
{

}

UI_Mouse::~UI_Mouse()
{
}

void UI_Mouse::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_cursor.png"));
			GameEngineSprite::CreateSingle("spr_cursor.png");
		}
	}
	//GameEngineCore::MainWindow.CursorOff();

	std::shared_ptr<GameEngineTexture> MouseTex = GameEngineTexture::Find("spr_cursor.png");

	UI_Cursor = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	UI_Cursor->SetSprite("spr_cursor.png");
	UI_Cursor->AutoSpriteSizeOn();
	

}

void UI_Mouse::Update(float _Delta)
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();
	float4 CamPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Half();

	UI_Cursor->Transform.SetLocalPosition({ (CamPos.X + MousePos.X - HalfWindowScale.hY()), -(CamPos.Y + MousePos.Y + HalfWindowScale.hY()) });
}
