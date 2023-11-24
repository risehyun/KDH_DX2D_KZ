#pragma once
#include "BaseLevel.h"
#include <GameEngineCore/GameEngineState.h>
#include "Map.h"
#include "Enemy.h"
#include "UITrigger.h"
#include "UI_FadeObject.h"
#include "GameStateManager.h"

class BossLevel1_2 : public BaseLevel
{
public:
	enum class LevelState
	{
		InitGame,
		PlayGame,
		SlowGame,
		ReverseGame,
		ReplayGame,
		Default
	};

	// constrcuter destructer
	BossLevel1_2();
	~BossLevel1_2();

	// delete Function
	BossLevel1_2(const BossLevel1_2& _Other) = delete;
	BossLevel1_2(BossLevel1_2&& _Other) noexcept = delete;
	BossLevel1_2& operator=(const BossLevel1_2& _Other) = delete;
	BossLevel1_2& operator=(BossLevel1_2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void FSM_Level_PlayGame();
	void FSM_Level_SlowGame();
	void FSM_Level_InitGame();
	void FSM_Level_ReverseGame();
	void FSM_Level_ReplayGame();

private:
	GameEngineState LevelState;
	std::shared_ptr<Map> MapObject;

	GameEngineSoundPlayer LevelFxPlayer;
	GameEngineSoundPlayer BGMPlayer;

	std::shared_ptr<UI_PlayUI> PlayUI = nullptr;
	std::shared_ptr<UITrigger> StageTriggerObject = nullptr;

	std::shared_ptr<UI_FadeObject> StageEndFadeObject = nullptr;
	std::shared_ptr<UI_FadeObject> StageStartFadeObject = nullptr;

	std::shared_ptr<GameStateManager> StateManager = nullptr;
};

