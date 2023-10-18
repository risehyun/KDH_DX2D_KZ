#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineGUI.h>

class TestGUIWindow : public GameEngineGUIWindow
{
public:
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};

class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer AmbiencePlayer;

	float4 HalfWindowScale;
};