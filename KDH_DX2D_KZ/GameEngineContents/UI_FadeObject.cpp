#include "PreCompile.h"
#include "UI_FadeObject.h"

#define UI_RESOURCE_FADETEXT "UI_YesThatShouldWork.png"

UI_FadeObject::UI_FadeObject()
{
}

UI_FadeObject::~UI_FadeObject()
{
}

void UI_FadeObject::SwitchFadeMode(int _Typeindex)
{
	int Type = _Typeindex;

	if (0 == Type)
	{
		FSM_FadeState.ChangeState(FSM_FadeState::In);
		return;
	}

	FSM_FadeState.ChangeState(FSM_FadeState::Out);
	return;
}

void UI_FadeObject::SetFadeObjectType(EFadeObjectType _Type)
{

	Type = _Type;

	// 리소스 로딩
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_FADE.png"));
			GameEngineSprite::CreateSingle("UI_FADE.png");

			GameEngineTexture::Load(FilePath.PlusFilePath(UI_RESOURCE_FADETEXT));
			GameEngineSprite::CreateSingle(UI_RESOURCE_FADETEXT);
		}
	}

	// 렌더러 생성
	FadeObjectRenderer = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::Skyline);

	if (Type == EFadeObjectType::Background)
	{
		FadeObjectRenderer->SetSprite("UI_FADE.png");
		float4 WindowScale = GameEngineCore::MainWindow.GetScale();
		FadeObjectRenderer->Transform.SetLocalScale(WindowScale);
	}
	else if (Type == EFadeObjectType::Text)
	{
		FadeObjectRenderer->SetSprite(UI_RESOURCE_FADETEXT);
		FadeObjectRenderer->AutoSpriteSizeOn();
	}

}

void UI_FadeObject::Start()
{
	FSM_Fade_In();
	FSM_Fade_Out();
}

void UI_FadeObject::Update(float _Delta)
{
	// FSM Stay 갱신
	FSM_FadeState.Update(_Delta);
}

void UI_FadeObject::FSM_Fade_In()
{
	CreateStateParameter FadeState_In_Param;

	FadeState_In_Param.Start = [=](class GameEngineState* _Parent)
	{

	};

	FadeState_In_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		FadeObjectRenderer->GetColorData().MulColor.A -= _Delta;

		if (false == IsUseInput && GetLiveTime() > 1.0f)
		{
			IsEnd = true;
			Death();
		}
	};

	FSM_FadeState.CreateState(FSM_FadeState::In, FadeState_In_Param);

}

void UI_FadeObject::FSM_Fade_Out()
{
	CreateStateParameter FadeState_Out_Param;

	FadeState_Out_Param.Start = [=](class GameEngineState* _Parent)
	{
		IsUseInput = true;
		FadeObjectRenderer->GetColorData().MulColor.A = 0.0f;
	};

	FadeState_Out_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		FadeObjectRenderer->GetColorData().MulColor.A += _Delta;

		if (FSM_FadeState.GetStateTime() > 1.0f)
		{
			IsEnd = true;
		}
	};

	FSM_FadeState.CreateState(FSM_FadeState::Out, FadeState_Out_Param);
}