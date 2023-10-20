#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "Map.h"
#include "UI_PlayUI.h"
#include <GameEngineCore/GameEngineState.h>

#include "BaseLevel.h"

enum class LevelState
{
	InitGame,
	PlayGame,
	SlowGame,
	ReverseGame,
	ReplayGame,
	Default
};

class MainLevel2_2 : public BaseLevel
{
public:
	// constrcuter destructer
	MainLevel2_2();
	~MainLevel2_2();

	// delete Function
	MainLevel2_2(const MainLevel2_2& _Other) = delete;
	MainLevel2_2(MainLevel2_2&& _Other) noexcept = delete;
	MainLevel2_2& operator=(const MainLevel2_2& _Other) = delete;
	MainLevel2_2& operator=(MainLevel2_2&& _Other) noexcept = delete;

	void FSM_Level_PlayGame();
	void FSM_Level_SlowGame();
	void FSM_Level_InitGame();

	//
//	void FSM_Intro_Start();
//	void FSM_StartGame_Start();

//	void FSM_Intro_Update(float _Delta);
//	void FSM_StartGame_Update(float _Delta);
	//

	float PressTime = 0.0f;
	float FreeTime = 0.0f;
//	int   CurBatteryIndex = 11;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineState LevelState;

	std::shared_ptr<Map> MapObject;

	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer SlowPlayer;

	std::shared_ptr<UI_PlayUI> PlayUI = nullptr;


};