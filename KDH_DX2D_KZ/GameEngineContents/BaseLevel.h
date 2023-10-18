#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "UI_PlayUI.h"

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

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void InitCameraSetting();

	//virtual enum class ELevelState
	//{
	//	Default,
	//};

//	ELevelState LevelState = ELevelState::Default;

	//virtual void ChangeLevelState(ELevelState _NextLevelState) {}
	//virtual void UpdateLevelState(float _Delta) {}

private:


	float4 CameraInitPos = float4::ZERO;
	GameEngineSoundPlayer BGMPlayer;
	std::shared_ptr<UI_PlayUI> PlayUIObject = nullptr;
};