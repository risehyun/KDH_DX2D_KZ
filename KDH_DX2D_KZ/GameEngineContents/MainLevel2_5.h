#pragma once
#include "BaseLevel.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "Map.h"

class MainLevel2_5 : public BaseLevel
{
public:
	// constrcuter destructer
	MainLevel2_5();
	~MainLevel2_5();

	// delete Function
	MainLevel2_5(const MainLevel2_5& _Other) = delete;
	MainLevel2_5(MainLevel2_5&& _Other) noexcept = delete;
	MainLevel2_5& operator=(const MainLevel2_5& _Other) = delete;
	MainLevel2_5& operator=(MainLevel2_5&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<Map> MapObject;
	GameEngineSoundPlayer BGMPlayer;
};

