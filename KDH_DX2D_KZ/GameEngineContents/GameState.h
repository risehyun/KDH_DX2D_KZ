#pragma once
#include <GameEngineCore/GameEngineObject.h>

class GameState : public GameEngineObject
{
	// constrcuter destructer
	GameState();
	~GameState();

	// delete Function
	GameState(const GameState& _Other) = delete;
	GameState(GameState&& _Other) noexcept = delete;
	GameState& operator=(const GameState& _Other) = delete;
	GameState& operator=(GameState&& _Other) noexcept = delete;

	bool GetGameState() const
	{
		return IsGameOver;
	}
	void SetGameOverOn()
	{
		IsGameOver = true;
	}
	void SetGameOverOff()
	{
		IsGameOver = false;
	}





protected:
	void Start() override;
	void Update(float _Delta) override;
//	void Release() override;

private:
	bool IsGameOver = false;
};

