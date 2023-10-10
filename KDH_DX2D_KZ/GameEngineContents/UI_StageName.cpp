#include "PreCompile.h"
#include "UI_StageName.h"

UI_StageName::UI_StageName()
{
}

UI_StageName::~UI_StageName()
{
}

void UI_StageName::InitStageNameData(EStageNameType _Type)
{
	Type = _Type;

	// 추후에 글로벌 변수로 아예 빼버릴 것
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// StageName
	UIRenderer_StageNameBackground = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
	UIRenderer_StageNameBackground->SetSprite("MapUIBackground.png");
	UIRenderer_StageNameBackground->AutoSpriteSizeOn();
	UIRenderer_StageNameBackground->Transform.SetLocalPosition(HalfWindowScale);

	if (Type == EStageNameType::Prison)
	{

		UIRenderer_StageNameCyan = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
		UIRenderer_StageNameCyan->SetSprite("StageName_MainLevel2_2_Cyan.png");
		UIRenderer_StageNameCyan->AutoSpriteSizeOn();
		UIRenderer_StageNameCyan->Transform.SetLocalPosition({ HalfWindowScale.X - 1000.f, HalfWindowScale.Y });


		UIRenderer_StageNameMagenta = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
		UIRenderer_StageNameMagenta->SetSprite("StageName_MainLevel2_2_magenta.png");
		UIRenderer_StageNameMagenta->AutoSpriteSizeOn();
		UIRenderer_StageNameMagenta->Transform.SetLocalPosition({ HalfWindowScale.X + 1000.f, HalfWindowScale.Y });


		UIRenderer_StageNameAll = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::UI);
		UIRenderer_StageNameAll->SetSprite("StageName_MainLevel2_2_All.png");
		UIRenderer_StageNameAll->AutoSpriteSizeOn();
		UIRenderer_StageNameAll->Transform.SetLocalPosition(HalfWindowScale);
		UIRenderer_StageNameAll->Off();
	}



}

void UI_StageName::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("MapUIBackground.png"));
			GameEngineSprite::CreateSingle("MapUIBackground.png");
		}
		

		// MainLevel2_2
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("StageName_MainLevel2_2_Cyan.png"));
			GameEngineSprite::CreateSingle("StageName_MainLevel2_2_Cyan.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("StageName_MainLevel2_2_magenta.png"));
			GameEngineSprite::CreateSingle("StageName_MainLevel2_2_magenta.png");
		}

		{
			GameEngineTexture::Load(FilePath.PlusFilePath("StageName_MainLevel2_2_All.png"));
			GameEngineSprite::CreateSingle("StageName_MainLevel2_2_All.png");
		}




		// MainLevel3_2
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("StageName_MainLevel3_2_All.png"));
			GameEngineSprite::CreateSingle("StageName_MainLevel3_2_All.png");
		}
	}


}

void UI_StageName::Update(float _Delta)
{
	float4 CyanRendererPos = UIRenderer_StageNameCyan->Transform.GetWorldPosition();
	float4 MagentaRendererPos = UIRenderer_StageNameMagenta->Transform.GetWorldPosition();

	float4 TargetPos = GameEngineCore::MainWindow.GetScale().Half();

	if (CyanRendererPos.X < TargetPos.X)
	{
		UIRenderer_StageNameCyan->Transform.AddWorldPosition({ 100.0f * _Delta * 10.0f, 0.0f });
	}

	if (MagentaRendererPos.X > TargetPos.X)
	{
		UIRenderer_StageNameMagenta->Transform.AddWorldPosition({ -100.0f * _Delta * 10.0f, 0.0f });
	}

	if (CyanRendererPos.X > TargetPos.X && MagentaRendererPos.X < TargetPos.X)
	{
		UIRenderer_StageNameCyan->Off();
		UIRenderer_StageNameMagenta->Off();
		UIRenderer_StageNameAll->On();
	}

}
