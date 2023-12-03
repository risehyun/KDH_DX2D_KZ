#pragma once
#include "Item.h"
#include "UI_GoArrow.h"

#define SLOT_DEFAULTNAME "spr_itemicons_0.png"

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
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_GameReplay;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_GameReplayExitText;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_GameReplayExitMouse;

	std::shared_ptr<GameEngineSpriteRenderer> UIRenderer_DashCoolTime;
	std::shared_ptr<GameEngineSpriteRenderer> UIRenderer_DashCoolTime_Background;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer_GoArrow;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer_PressKeyboard;

	void SetItemSlot(std::string_view _ItemName);

	bool IsHasItemInSlot() const
	{
		// 만약 현재 아이템이 디폴트 값과 다르다면 슬롯에 아이템이 있는 것으로 간주합니다.
		if (ItemName != SlotDefaultName)
		{
			return true;
		}

		return false;
	}

	std::string_view GetItemInfoInSlot() const
	{
		return ItemName;
	};

	void Update_ItemSlot();

	void OffBatteryParts(int _PartsIndex);
	void OnBatteryParts(int _PartsIndex);

	void UsePresentText();
	void UseHUD();
	void InactiveHUD();
	void UseBattery();
	void UseTimer();
	void UseWeapon();
	void UseItem();

	void OnGameOverUI();
	void OffGameOverUI();

	void OnGoArrowUI();
	void OffGoArrowUI();

	// ★ 이렇게 하지 말고 나중에 하나로 묶어서, UI또 개별 클래스로 따로 두기
	void SetGoArrowLeft();
	void SetGoArrowRight();
	void MovingGoArrow(float _Delta);


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

	void Set_UIGameReplay_Off()
	{
		UIRenderer_GameReplay->Off();
		UIRenderer_GameReplayExitText->Off();
		UIRenderer_GameReplayExitMouse->Off();
	}

	void Set_UIGameReplay_On()
	{
		UIRenderer_GameReplay->On();
		UIRenderer_GameReplayExitText->On();
		UIRenderer_GameReplayExitMouse->On();
	}

	std::shared_ptr<GameEngineUIRenderer> Get_UIGameReplay()
	{
		return UIRenderer_GameReplay;
	}

	std::string_view SlotDefaultName = SLOT_DEFAULTNAME;
	std::string_view ItemName = SlotDefaultName;

	float4 TimerInitScale = float4::ZERO;
	float4 CoolTimerInitScale = float4::ZERO;


	std::shared_ptr<UI_GoArrow> GoArrow_UI = nullptr;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float ArrowMoveTimer = 0.0f;
	float4 NextPos = { 1.0f, 0.0f };


};

