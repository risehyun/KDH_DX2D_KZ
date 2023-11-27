#pragma once
#include "BaseLevel.h"
#include "Map.h"
#include "Portal.h"
#include "Enemy.h"
#include "UITrigger.h"
#include "UI_FadeObject.h"
#include "GameStateManager.h"
#include "Door.h"

class MainLevel2_4 : public BaseLevel
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
	MainLevel2_4();
	~MainLevel2_4();

	// delete Function
	MainLevel2_4(const MainLevel2_4& _Other) = delete;
	MainLevel2_4(MainLevel2_4&& _Other) noexcept = delete;
	MainLevel2_4& operator=(const MainLevel2_4& _Other) = delete;
	MainLevel2_4& operator=(MainLevel2_4&& _Other) noexcept = delete;

	std::vector<std::shared_ptr<Enemy>> AllSpawnedEnemy;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void FSM_Level_PlayGame();
	void FSM_Level_SlowGame();
	void FSM_Level_InitGame();
	void FSM_Level_ReplayGame();
	void FSM_Level_ReverseGame();

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

	std::shared_ptr<Door> DoorObject = nullptr;
};