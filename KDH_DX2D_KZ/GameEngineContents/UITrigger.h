#pragma once
#include "InteractableObject.h"

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

//	void InitUITriggerData(std::string_view _NextLevelName, bool _IsUsingInput);

protected:
	void Start() override;
	void Update(float _Delta) override;

};

