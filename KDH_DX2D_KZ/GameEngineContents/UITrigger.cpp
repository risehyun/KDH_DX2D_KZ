#include "PreCompile.h"
#include "UITrigger.h"
#include "UI_PlayUI.h"

UITrigger::UITrigger()
{
}

UITrigger::~UITrigger()
{
}

void UITrigger::InitUITriggerData(TriggerType _Type)
{
	Type = _Type;

	if (Type == TriggerType::KeyboardW)
	{
		InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
		InteractCollision->Transform.SetLocalScale({ 100.0f, 500.0f, 1.0f });
	}

	if (Type == TriggerType::GoArrow)
	{
		InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
		InteractCollision->Transform.SetLocalScale({ 400.0f, 500.0f, 1.0f });
	}

}

void UITrigger::PressKeyboardWEvent()
{
	EventParameter InteractEvent;

	InteractEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		UI_PlayUI* UIPtr = UI_PlayUI::PlayUI;
		UIPtr->Renderer_PressKeyboard->ChangeAnimation("PressKeyboardW");

		_this->Off();
	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, InteractEvent);
}

void UITrigger::ArrowUIEvent()
{
	EventParameter InteractEvent;

	InteractEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		UI_PlayUI* UIPtr = UI_PlayUI::PlayUI;
		UIPtr->Renderer_GoArrow->On();
		UIPtr->Renderer_PressKeyboard->Off();

//		_this->Off();
	};

	InteractEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		UITrigger* TriggerPtr = dynamic_cast<UITrigger*>(thisActor);

		TriggerPtr->Duration += GameEngineCore::MainTime.GetDeltaTime();

		UI_PlayUI* UIPtr = UI_PlayUI::PlayUI;
		UIPtr->Renderer_GoArrow->On();
		UIPtr->Renderer_PressKeyboard->Off();

		if (TriggerPtr->Duration > 3.0f)
		{
			UIPtr->UIRenderer_GoArrow->Off();
			_this->Off();
		}
	};

	InteractEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		UI_PlayUI* UIPtr = UI_PlayUI::PlayUI;
		UIPtr->Renderer_GoArrow->Off();
	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, InteractEvent);
}

void UITrigger::Start()
{


}

void UITrigger::Update(float _Delta)
{
	if (Type == TriggerType::KeyboardW)
	{
		PressKeyboardWEvent();
	}

	if (Type == TriggerType::GoArrow)
	{
		ArrowUIEvent();
	}
}

// 추후 수정
//void UITrigger::InitUITriggerData(std::string_view _NextLevelName, bool _IsUsingInput)
//{
//}
