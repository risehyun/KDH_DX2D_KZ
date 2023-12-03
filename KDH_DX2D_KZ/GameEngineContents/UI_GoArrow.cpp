#include "PreCompile.h"
#include "UI_GoArrow.h"

UI_GoArrow::UI_GoArrow()
{
}

UI_GoArrow::~UI_GoArrow()
{
}

void UI_GoArrow::Start()
{

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_GoAll.png"));
			GameEngineSprite::CreateSingle("UI_GoAll.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_GoAll_Left.png"));
			GameEngineSprite::CreateSingle("UI_GoAll_Left.png");
		}
	}

	UIRenderer_GoArrow = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_GoArrow->SetSprite("UI_GoAll.png");
	UIRenderer_GoArrow->AutoSpriteSizeOn();
	UIRenderer_GoArrow->Transform.SetLocalPosition({ 1180.0f, 200.0f, 0.f, 1.0f });
	UIRenderer_GoArrow->Off();
}

void UI_GoArrow::Update(float _Delta)
{
	MovingGoArrow(_Delta);
}

void UI_GoArrow::OnRenderer()
{
	if (false == UIRenderer_GoArrow->GetUpdateValue())
	{
		UIRenderer_GoArrow->On();
	}
}

void UI_GoArrow::OffRenderer()
{
	if (true == UIRenderer_GoArrow->GetUpdateValue())
	{
		UIRenderer_GoArrow->Off();
	}
}

void UI_GoArrow::SetGoArrowData(float4 _Dir, float4 _InitPos)
{
	Dir = _Dir;
	InitPos = _InitPos;

	Transform.SetWorldPosition(InitPos);

	if (Dir == float4::LEFT)
	{
		UIRenderer_GoArrow->SetSprite("UI_GoAll_Left.png");
	}

	else if (Dir == float4::RIGHT)
	{
		UIRenderer_GoArrow->SetSprite("UI_GoAll.png");
	}
}

void UI_GoArrow::MovingGoArrow(float _Delta)
{
	ArrowMoveTimer += _Delta;

	if (ArrowMoveTimer < 0.5f)
	{
		NextPos = { 1.0f, 0.0f };
	}
	else if (ArrowMoveTimer > 0.5f && ArrowMoveTimer < 1.0f)
	{
		NextPos = { -1.0f, 0.0f };
	}
	else
	{
		UIRenderer_GoArrow->Transform.SetWorldPosition(InitPos);
		NextPos = float4::ZERO;
		ArrowMoveTimer = 0.0f;
	}

	UIRenderer_GoArrow->Transform.AddWorldPosition(NextPos);

}