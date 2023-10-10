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



	std::shared_ptr<GameEngineUIRenderer> UIRenderer_Hud;



	std::shared_ptr<GameEngineSpriteRenderer> UIRenderer_GoArrow;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer_PressKeyboard;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:


};

