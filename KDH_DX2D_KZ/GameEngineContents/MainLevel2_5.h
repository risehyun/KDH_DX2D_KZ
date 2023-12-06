#pragma once
#include "BaseLevel.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "Map.h"
#include "UITrigger.h"
#include "UI_FadeObject.h"
#include "GameStateManager.h"
#include "Enemy.h"
#include "Door.h"
// #include "Item.h"

class MainLevel2_5 : public BaseLevel
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
	MainLevel2_5();
	~MainLevel2_5();

	// delete Function
	MainLevel2_5(const MainLevel2_5& _Other) = delete;
	MainLevel2_5(MainLevel2_5&& _Other) noexcept = delete;
	MainLevel2_5& operator=(const MainLevel2_5& _Other) = delete;
	MainLevel2_5& operator=(MainLevel2_5&& _Other) noexcept = delete;

	std::vector<std::shared_ptr<Enemy>> AllSpawnedEnemy;


//	std::shared_ptr<Item> BeerItem;

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

	std::vector<std::shared_ptr<Door>> AllDoorObject;

};

