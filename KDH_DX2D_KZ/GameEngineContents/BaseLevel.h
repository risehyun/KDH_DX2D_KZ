#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "UI_PlayUI.h"
#include <GameEngineCore/GameEngineState.h>
#include <GameEnginePlatform/GameEngineSound.h>

//enum class LevelState
//{
//	Intro,
//	PlayGame,
//	SlowGame,
//	ReverseGame,
//	ReplayGame,
//	Default
//};

class BaseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BaseLevel();
	~BaseLevel();

	// delete Function
	BaseLevel(const BaseLevel& _Other) = delete;
	BaseLevel(BaseLevel&& _Other) noexcept = delete;
	BaseLevel& operator=(const BaseLevel& _Other) = delete;
	BaseLevel& operator=(BaseLevel&& _Other) noexcept = delete;

	// 게임 스테이트로 옮기기
	float PressTimeControlTime = 0.0f;
	float FreeTimeControlTime = 0.0f;
	int   CurBatteryIndex = 11;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void InitCameraSetting();

	//void FSM_Level_PlayGame();
	//void FSM_Level_SlowGame();

//	GameEngineState LevelState;

private:
	GameEngineSoundPlayer BGMPlayer;
//	GameEngineSoundPlayer SlowPlayer;

	float4 CameraInitPos = float4::ZERO;
	std::shared_ptr<UI_PlayUI> PlayUIObject = nullptr;
};