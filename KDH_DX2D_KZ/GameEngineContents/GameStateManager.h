#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameStateManager : public GameEngineActor
{
public:
	// constrcuter destructer
	GameStateManager();
	~GameStateManager();

	// delete Function
	GameStateManager(const GameStateManager& _Other) = delete;
	GameStateManager(GameStateManager&& _Other) noexcept = delete;
	GameStateManager& operator=(const GameStateManager& _Other) = delete;
	GameStateManager& operator=(GameStateManager&& _Other) noexcept = delete;

	static GameStateManager* GameState;

	bool GetCurrentGameState() const
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
