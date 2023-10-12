#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "Map.h"

class MainLevel2_3 : public GameEngineLevel
{
public:
	// constrcuter destructer
	MainLevel2_3();
	~MainLevel2_3();

	// delete Function
	MainLevel2_3(const MainLevel2_3& _Other) = delete;
	MainLevel2_3(MainLevel2_3&& _Other) noexcept = delete;
	MainLevel2_3& operator=(const MainLevel2_3& _Other) = delete;
	MainLevel2_3& operator=(MainLevel2_3&& _Other) noexcept = delete;

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
			

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<Map> MapObject;
	GameEngineSoundPlayer BGMPlayer;
};