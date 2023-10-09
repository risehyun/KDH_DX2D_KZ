#include "PreCompile.h"
#include "UITrigger.h"
#include "UI_PlayUI.h"

UITrigger::UITrigger()
{
}

UITrigger::~UITrigger()
{
}

void UITrigger::Start()
{
	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->Transform.SetLocalScale({ 100, 500, 1 });
}

void UITrigger::Update(float _Delta)
{
	EventParameter InteractEvent;

	InteractEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		UI_PlayUI* UIPtr = UI_PlayUI::PlayUI;
		UIPtr->Renderer_PressKeyboard->ChangeAnimation("PressKeyboardW");
	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, InteractEvent);
}

// 추후 수정
//void UITrigger::InitUITriggerData(std::string_view _NextLevelName, bool _IsUsingInput)
//{
//}
