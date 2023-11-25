#pragma once
#include "InteractableObject.h"

enum class TriggerType
{
	KeyboardAD,
	KeyboardW,
	GoArrow,
	StageClear,
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
	void GameClearTriggerEvent();

	void SetTriggerScale(float4 &_TriggerScale);

	TriggerType Type = TriggerType::Default;

	bool GetPlayerDetect()
	{
		return IsDetectPlayer;
	}

	void SetPlayerDetectOff()
	{
		IsDetectPlayer = false;
	}

	void SetMainCollisionScale(float4 _NewScale)
	{
		InteractCollision->Transform.SetLocalScale(_NewScale);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float Duration = 0.0f;
	bool IsDetectPlayer = false;
};

