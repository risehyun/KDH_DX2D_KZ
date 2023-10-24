#pragma once
class UI_PlayUI : public GameEngineActor
{
public:
	UI_PlayUI();
	~UI_PlayUI();

	UI_PlayUI(const UI_PlayUI& _Other) = delete;
	UI_PlayUI(UI_PlayUI&& _Other) noexcept = delete;
	UI_PlayUI& operator=(const UI_PlayUI& _Other) = delete;
	UI_PlayUI& operator=(UI_PlayUI&& _Other) noexcept = delete;

	static UI_PlayUI* PlayUI;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_LeftClick;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_PresentText;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_GoArrow;


	std::shared_ptr<GameEngineUIRenderer> UIRenderer_Hud;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_Timer;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> UIRenderer_BatteryParts;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_WeaponIcon;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_ItemIcon;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_GameOver;


	std::shared_ptr<GameEngineSpriteRenderer> UIRenderer_DashCoolTime;
	std::shared_ptr<GameEngineSpriteRenderer> UIRenderer_DashCoolTime_Background;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer_GoArrow;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer_PressKeyboard;

	void OffBatteryParts(int _PartsIndex);
	void OnBatteryParts(int _PartsIndex);

	void UsePresentText();
	void UseHUD();
	void UseBattery();
	void UseTimer();
	void UseWeapon();
	void UseItem();

	void OnGameOverUI();
	void OffGameOverUI();

	void OnGoArrow();

	void SetTimerUIScale(float _TimeDecreaseAmount)
	{
		float NextTimerXScale = TimerInitScale.X * _TimeDecreaseAmount;
		UIRenderer_Timer->Transform.SetWorldScale({ NextTimerXScale, TimerInitScale.Y, TimerInitScale.Z });
	}

	void SetDashCoolTimeUIScale(float _TimeDecreaseAmount)
	{
		float NextTimerXScale = CoolTimerInitScale.X * _TimeDecreaseAmount;
		UIRenderer_DashCoolTime->Transform.SetWorldScale({ NextTimerXScale, CoolTimerInitScale.Y, CoolTimerInitScale.Z });
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float4 TimerInitScale = float4::ZERO;
	float4 CoolTimerInitScale = float4::ZERO;
};

