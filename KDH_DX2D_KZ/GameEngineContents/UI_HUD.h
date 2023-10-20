#pragma once
#include "HUD_Battery.h"
class UI_HUD : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_HUD();
	~UI_HUD();

	// delete Function
	UI_HUD(const UI_HUD& _Other) = delete;
	UI_HUD(UI_HUD&& _Other) noexcept = delete;
	UI_HUD& operator=(const UI_HUD& _Other) = delete;
	UI_HUD& operator=(UI_HUD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	
private:
	std::shared_ptr<class GameEngineUIRenderer> HudMainRenderer;


	std::shared_ptr<HUD_Battery> Battery;
};