#pragma once
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
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_StageClearText;


};

