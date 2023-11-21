#include "PreCompile.h"
#include "UI_StageClear.h"
#include "UI_FadeObject.h"
#include "Player.h"

UI_StageClear::UI_StageClear()
{
}

UI_StageClear::~UI_StageClear()
{
}

void UI_StageClear::Start()
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	FadeBackgroundObject = GetLevel()->CreateActor<UI_FadeObject>();
	FadeBackgroundObject->SetFadeObjectType(EFadeObjectType::Background);
	FadeBackgroundObject->SwitchFadeMode(1);

	FadeTextObject = GetLevel()->CreateActor<UI_FadeObject>();
	FadeTextObject->SetFadeObjectType(EFadeObjectType::Text);
	FadeTextObject->SwitchFadeMode(1);
	FadeTextObject->Transform.SetLocalPosition({ HalfWindowScale.X, HalfWindowScale.Y - 100.0f});

}

void UI_StageClear::Update(float _Delta)
{
	if (GetLiveTime() > 1.5f)
	{
		FadeBackgroundObject->SwitchFadeMode(0);
		FadeTextObject->SwitchFadeMode(0);
	}
}
