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

	// ★ 벡터여야 한다
	std::vector<std::shared_ptr<GameEngineUIRenderer>> UIRenderer_BatteryParts;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_WeaponIcon;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_ItemIcon;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_GameOver;


	std::shared_ptr<GameEngineSpriteRenderer> Renderer_GoArrow;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer_PressKeyboard;

	void UsePresentText();
	void UseHUD();

	void OnGameOverUI();
	void OffGameOverUI();

	void OnGoArrow();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

