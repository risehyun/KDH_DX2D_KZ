#pragma once

enum class EStageNameType
{
	Prison,
	Bunker,
	Default,
};

class UI_StageName : public GameEngineActor
{
public:
	UI_StageName();
	~UI_StageName();

	UI_StageName(const UI_StageName& _Other) = delete;
	UI_StageName(UI_StageName&& _Other) noexcept = delete;
	UI_StageName& operator=(const UI_StageName& _Other) = delete;
	UI_StageName& operator=(UI_StageName&& _Other) noexcept = delete;

	void InitStageNameData(EStageNameType _Type);

	EStageNameType Type = EStageNameType::Default;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_StageNameBackground;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_StageNameCyan;
	std::shared_ptr<GameEngineUIRenderer> UIRenderer_StageNameMagenta;

	std::shared_ptr<GameEngineUIRenderer> UIRenderer_StageNameAll;

};

