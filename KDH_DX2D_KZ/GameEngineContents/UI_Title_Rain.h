#pragma once

class UI_Title_Rain : public GameEngineActor
{
public:
	UI_Title_Rain();
	~UI_Title_Rain();

	UI_Title_Rain(const UI_Title_Rain& _Other) = delete;
	UI_Title_Rain(UI_Title_Rain&& _Other) noexcept = delete;
	UI_Title_Rain& operator=(const UI_Title_Rain& _Other) = delete;
	UI_Title_Rain& operator=(UI_Title_Rain&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> RainRenderer;

	float RainDeathPos = 0.f;
};