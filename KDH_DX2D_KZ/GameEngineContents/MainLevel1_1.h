#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Map.h"
#include <GameEnginePlatform/GameEngineSound.h>

class MainLevel1_1 : public GameEngineLevel
{
public:
	// constrcuter destructer
	MainLevel1_1();
	~MainLevel1_1();

	// delete Function
	MainLevel1_1(const MainLevel1_1& _Other) = delete;
	MainLevel1_1(MainLevel1_1&& _Other) noexcept = delete;
	MainLevel1_1& operator=(const MainLevel1_1& _Other) = delete;
	MainLevel1_1& operator=(MainLevel1_1&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void ShakeCamera(float _Delta);

private:
	std::shared_ptr<Map> MapObject;

	GameEngineSoundPlayer BGMPlayer;

	float4 CameraInitPos;
};

