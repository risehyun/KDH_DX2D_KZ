#pragma once
#include "InteractableObject.h"

enum class TriggerType
{
	KeyboardAD,
	KeyboardW,
	GoArrow,
	StairIn,
	StairOut,
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

	// �Լ�����Ʈ�� ���� ����, Ŭ���� �̸��� EventTrigger�� ������ ��
	void PressKeyboardWEvent();
	void ArrowUIEvent();
	void StairInEvent();

	TriggerType Type = TriggerType::Default;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float Duration = 0.0f;

	char stairDownKey = ' ';
	char stairUpKey = ' ';

};

