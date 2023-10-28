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

	if (Type == TriggerType::StairIn)
	{
		InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
		InteractCollision->Transform.SetLocalScale({ 320.0f, 480.0f, 1.0f });
		InteractCollision->SetCollisionType(ColType::AABBBOX2D);
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

// ★ 몬스터 방향에 따라 처리하는 로직은 추후 일반화해서 추가.
// 몬스터는 키를 입력받지 않으므로 순수하게 현재 방향에 따라서 처리 해야 함.
void UITrigger::PlayerStairInEvent()
{
	EventParameter InteractEvent;

	InteractEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		UITrigger* TriggerPtr = dynamic_cast<UITrigger*>(thisActor);

		Player::MainPlayer->DirCheck();
		TriggerPtr->CharacterInDir = Player::MainPlayer->GetPlayerDir();

		if (TriggerPtr->CharacterInDir == float4::LEFT)
		{
			TriggerPtr->stairUpKey = 'A';
			TriggerPtr->stairDownKey = 'D';
		}
		else if (TriggerPtr->CharacterInDir == float4::RIGHT)
		{
			TriggerPtr->stairUpKey = 'D';
			TriggerPtr->stairDownKey = 'A';
		}
	};

	InteractEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		UITrigger* TriggerPtr = dynamic_cast<UITrigger*>(thisActor);

		Player::MainPlayer->DirCheck();


		TriggerPtr->CharacterInDir = Player::MainPlayer->GetPlayerDir();

		if (TriggerPtr->CharacterInDir == float4::LEFT)
		{
			TriggerPtr->stairUpKey = 'A';
			TriggerPtr->stairDownKey = 'D';
		}
		else if (TriggerPtr->CharacterInDir == float4::RIGHT)
		{
			TriggerPtr->stairUpKey = 'D';
			TriggerPtr->stairDownKey = 'A';
		}

		if (true == Player::MainPlayer->GetGroundPixelCollision())
		{

			Player::MainPlayer->GravityPower = 1000.0f;
			// in, out key에 따라 보간
			if (GameEngineInput::IsPress(TriggerPtr->stairDownKey, TriggerPtr))
			{
				Player::MainPlayer->Transform.AddWorldPosition(float4::DOWN * GameEngineCore::MainTime.GetDeltaTime() * Player::MainPlayer->Speed);
			}
			
		}
		else
		{
			Player::MainPlayer->GravityPower = 200.0f;

			if (GameEngineInput::IsPress(TriggerPtr->stairUpKey, TriggerPtr))
			{
				Player::MainPlayer->Transform.AddWorldPosition(float4::UP * GameEngineCore::MainTime.GetDeltaTime() * Player::MainPlayer->Speed);
			}
		}


	};

	InteractEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		UITrigger* TriggerPtr = dynamic_cast<UITrigger*>(thisActor);

		TriggerPtr->stairUpKey = ' ';
		TriggerPtr->stairDownKey = ' ';
	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, InteractEvent);
}

void UITrigger::EnemyStairInEvent()
{
	EventParameter InteractEvent;

	InteractEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		UITrigger* TriggerPtr = dynamic_cast<UITrigger*>(thisActor);

		GameEngineActor* EnemyActor = Col->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(EnemyActor);

		EnemyPtr->DirCheck();
		TriggerPtr->CharacterInDir = EnemyPtr->GetEnemyDir();

		if (true == EnemyPtr->GetGroundPixelCollision())
		{
			EnemyPtr->GravityPower = 1000.0f;
			EnemyPtr->Transform.AddWorldPosition(float4::DOWN);
		}
		else
		{
			EnemyPtr->GravityPower = 200.0f;

			if (TriggerPtr->CharacterInDir == float4::LEFT)
			{
				EnemyPtr->Transform.SetWorldPosition(float4::UP);
			}
			else if (TriggerPtr->CharacterInDir == float4::RIGHT)
			{
				EnemyPtr->Transform.AddWorldPosition(float4::UP);
			}
		}


	};

	InteractEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		UITrigger* TriggerPtr = dynamic_cast<UITrigger*>(thisActor);

		GameEngineActor* EnemyActor = Col->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(EnemyActor);

		EnemyPtr->DirCheck();
		TriggerPtr->CharacterInDir = EnemyPtr->GetEnemyDir();

		if (true == EnemyPtr->GetGroundPixelCollision())
		{
			EnemyPtr->GravityPower = 1000.0f;
			EnemyPtr->Transform.AddWorldPosition((TriggerPtr->CharacterInDir + float4::DOWN) * GameEngineCore::MainTime.GetDeltaTime() * EnemyPtr->Speed);
		}
		else
		{
			EnemyPtr->GravityPower = 200.0f;

			if (TriggerPtr->CharacterInDir == float4::LEFT)
			{
				EnemyPtr->Transform.AddWorldPosition((float4::RIGHT + float4::UP) * GameEngineCore::MainTime.GetDeltaTime() * EnemyPtr->Speed);

			}
			else if (TriggerPtr->CharacterInDir == float4::RIGHT)
			{
				EnemyPtr->Transform.AddWorldPosition((float4::LEFT + float4::UP) * GameEngineCore::MainTime.GetDeltaTime() * EnemyPtr->Speed);
			}
		}


	};

	InteractEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

	};

	InteractCollision->CollisionEvent(ContentsCollisionType::EnemyBody, InteractEvent);

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
	if (Type == TriggerType::KeyboardW)
	{
		PressKeyboardWEvent();
	}

	if (Type == TriggerType::GoArrow)
	{
		ArrowUIEvent();
	}

	if (Type == TriggerType::StairIn)
	{
		PlayerStairInEvent();
		EnemyStairInEvent();
	}
}

// 추후 수정
//void UITrigger::InitUITriggerData(std::string_view _NextLevelName, bool _IsUsingInput)
//{
//}
