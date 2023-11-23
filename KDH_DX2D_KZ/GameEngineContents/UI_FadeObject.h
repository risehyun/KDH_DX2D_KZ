#pragma once
#include <GameEngineCore/GameEngineState.h>


enum class FSM_FadeState
{
	In,
	Out,
	Default
};

enum class EFadeObjectType
{
	Background,
	Text,
	Default
};

class UI_FadeObject : public GameEngineActor
{
public:
	UI_FadeObject();
	~UI_FadeObject();

	UI_FadeObject(const UI_FadeObject& _Other) = delete;
	UI_FadeObject(UI_FadeObject&& _Other) noexcept = delete;
	UI_FadeObject& operator=(const UI_FadeObject& _Other) = delete;
	UI_FadeObject& operator=(UI_FadeObject&& _Other) noexcept = delete;


	void UseUserInput()
	{
		IsUseInput = true;
	}


	// 새로운 FSM 적용
	GameEngineState FSM_FadeState;


	EFadeObjectType Type = EFadeObjectType::Background;


	std::shared_ptr<GameEngineUIRenderer> FadeObjectRenderer;

	void SwitchFadeMode(int _Typeindex = 0);

	void SetFadeObjectType(EFadeObjectType _Type);

	bool IsEnd = false;

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineColor FadeColor;




	bool IsUseInput = false;
	float CurrentAlpha = 0.0f;

	// FSM
	void FSM_Fade_In();
	void FSM_Fade_Out();
};

