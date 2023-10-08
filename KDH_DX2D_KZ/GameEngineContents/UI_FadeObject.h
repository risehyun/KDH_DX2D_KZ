#pragma once

class UI_FadeObject : public GameEngineActor
{
public:
	enum class EFADE_STATE
	{
		In,
		Out,
		Default
	};

public:
	UI_FadeObject();
	~UI_FadeObject();

	UI_FadeObject(const UI_FadeObject& _Other) = delete;
	UI_FadeObject(UI_FadeObject&& _Other) noexcept = delete;
	UI_FadeObject& operator=(const UI_FadeObject& _Other) = delete;
	UI_FadeObject& operator=(UI_FadeObject&& _Other) noexcept = delete;

	EFADE_STATE FadeState = EFADE_STATE::In;

	void SwitchFadeMode(EFADE_STATE _ChangeState);
	void Fade(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

	void StateUpdate(float _Delta);

	GameEngineColor FadeColor;

	std::shared_ptr<GameEngineUIRenderer> FadeObjectRenderer;

	float CurrentAlpha = 0.0f;
};

