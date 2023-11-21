#pragma once
#include "UI_FadeObject.h"

class UI_StageClear : public GameEngineActor
{
public:
	UI_StageClear();
	~UI_StageClear();

	UI_StageClear(const UI_StageClear& _Other) = delete;
	UI_StageClear(UI_StageClear&& _Other) noexcept = delete;
	UI_StageClear& operator=(const UI_StageClear& _Other) = delete;
	UI_StageClear& operator=(UI_StageClear&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> UIRenderer_StageClearText;

	std::shared_ptr<UI_FadeObject> FadeBackgroundObject = nullptr;
	std::shared_ptr<UI_FadeObject> FadeTextObject = nullptr;
};

