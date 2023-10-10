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