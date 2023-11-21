#include "PreCompile.h"
#include "UITrigger.h"
#include "UI_PlayUI.h"
#include "Player.h"
#include "Enemy.h"

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

	if (Type == TriggerType::StageClear)
	{
		InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
		InteractCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
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

void UITrigger::GameClearTriggerEvent()
{
	EventParameter InteractEvent;

	InteractEvent.Enter = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		IsDetectPlayer = true;
		_this->Off();
	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, InteractEvent);
}

void UITrigger::SetTriggerScale(float4 &_TriggerScale)
{
	InteractCollision->Transform.SetLocalScale(_TriggerScale);
}

void UITrigger::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UITrigger::Update(float _Delta)
{

	if (true == InteractCollision->GetUpdateValue())
	{
		if (Type == TriggerType::KeyboardW)
		{
			PressKeyboardWEvent();
		}

		if (Type == TriggerType::GoArrow)
		{
			ArrowUIEvent();
		}

		if (Type == TriggerType::StageClear)
		{
			GameClearTriggerEvent();
		}
	}
}