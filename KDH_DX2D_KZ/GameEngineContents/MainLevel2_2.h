#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "Map.h"
#include "UI_PlayUI.h"

class MainLevel2_2 : public GameEngineLevel
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

	// 상위 Level 클래스로 이동
	enum class ELevelState
	{
		Intro,
		StartGame,
		Default,
	};

	ELevelState LevelState = ELevelState::Default;

	void ChangeLevelState(ELevelState _NextLevelState);
	void UpdateLevelState(float _Delta);

	void FSM_Intro_Start();
	void FSM_StartGame_Start();

	void FSM_Intro_Update(float _Delta);
	void FSM_StartGame_Update(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<Map> MapObject;
	GameEngineSoundPlayer BGMPlayer;

	std::shared_ptr<UI_PlayUI> PlayUIObject = nullptr;
};