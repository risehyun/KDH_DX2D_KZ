#pragma once
#include "BaseLevel.h"
#include "Map.h"
#include "Portal.h"

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

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void FSM_Level_PlayGame();
	void FSM_Level_SlowGame();
	void FSM_Level_InitGame();

private:
	GameEngineState LevelState;
	std::shared_ptr<Map> MapObject;

	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer SlowPlayer;

	std::shared_ptr<UI_PlayUI> PlayUI = nullptr;
	std::shared_ptr<Portal> PortalObject = nullptr;
};

