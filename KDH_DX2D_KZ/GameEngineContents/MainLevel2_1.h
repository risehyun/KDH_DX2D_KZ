#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Map.h"

class MainLevel2_1 : public GameEngineLevel
{
public:
	// constrcuter destructer
	MainLevel2_1();
	~MainLevel2_1();

	// delete Function
	MainLevel2_1(const MainLevel2_1& _Other) = delete;
	MainLevel2_1(MainLevel2_1&& _Other) noexcept = delete;
	MainLevel2_1& operator=(const MainLevel2_1& _Other) = delete;
	MainLevel2_1& operator=(MainLevel2_1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<Map> MapObject;

};