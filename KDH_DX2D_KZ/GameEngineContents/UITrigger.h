#pragma once
#include "InteractableObject.h"

enum class TriggerType
{
	KeyboardAD,
	KeyboardW,
	GoArrow,
	StairIn,
	Default,
};

class UITrigger : public InteractableObject
{

public:
	// constrcuter destructer
	UITrigger();
	~UITrigger();

	// delete Function
	UITrigger(const UITrigger& _Other) = delete;
	UITrigger(UITrigger&& _Other) noexcept = delete;
	UITrigger& operator=(const UITrigger& _Other) = delete;
	UITrigger& operator=(UITrigger&& _Other) noexcept = delete;

	void InitUITriggerData(TriggerType _Type);

	// 함수포인트로 추후 변경, 클래스 이름도 EventTrigger로 변경할 것
	void PressKeyboardWEvent();
	void ArrowUIEvent();
	void PlayerStairInEvent();
	void EnemyStairInEvent();

	void SetTriggerScale(float4 &_TriggerScale);

	TriggerType Type = TriggerType::Default;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float Duration = 0.0f;

	char stairDownKey = ' ';
	char stairUpKey = ' ';

	float4 CharacterInDir = float4::ZERO;
};

