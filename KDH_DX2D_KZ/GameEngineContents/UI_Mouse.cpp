#include "PreCompile.h"
#include "UI_Mouse.h"


UI_Mouse* UI_Mouse::Mouse = nullptr;

UI_Mouse::UI_Mouse()
{
	Mouse = this;
}

UI_Mouse::~UI_Mouse()
{
}

// ���콺�� ���� ���� ��ǥ�� 2D���� ��ǥ�� ���ؼ� �������ݴϴ�.
float4 UI_Mouse::GetMouseWorldPositionToActor()
{
	float4 MouseWorldPosToActor = GetLevel()->GetMainCamera()->Transform.GetWorldPosition() + GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	return MouseWorldPosToActor;
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
	
//	GameEngineCore::MainWindow.CursorOff();

	std::shared_ptr<GameEngineTexture> MouseTex = GameEngineTexture::Find("spr_cursor.png");

	MouseRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	MouseRenderer->SetSprite("spr_cursor.png");
	MouseRenderer->AutoSpriteSizeOn();
	
	MouseCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	MouseCollision->Transform.SetLocalScale({ 30, 30, 1 });

}

void UI_Mouse::Update(float _Delta)
{
	// ���콺 ��ġ
	float4 WorldMousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	MouseRenderer->Transform.SetLocalPosition({ WorldMousePos.X, WorldMousePos.Y });



	// ���� ��ǥ ���� ���� ��ġ ����
	MouseWorldToActorPos = GetMouseWorldPositionToActor();


//	MouseCollision->Transform.SetLocalPosition(WorldMousePos);
}
