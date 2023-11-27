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

	bool GetCurrentGameClear() const
	{
		return IsGameClear;
	}

	void SetGameClearOn()
	{
		IsGameClear = true;
	}

	void SetGameClearOff()
	{
		IsGameClear = false;
	}

	int GetCurTimeControlBattery() const
	{
		return CurTimeControlBattery;
	}

	int MaxTimeControlBattery = 11;
	int CurTimeControlBattery = 0;

	void ResetTimeControlBattery()
	{
		CurTimeControlBattery = MaxTimeControlBattery;
	}

	void ResetLeftEnemyCount()
	{
		LeftEnemy = InitEnemyCount;
	}

	void InitEnemyTotalCount(int _Count)
	{
		InitEnemyCount = _Count;
		LeftEnemy = InitEnemyCount;
	}

	int InitEnemyCount = 0;
	int LeftEnemy = 0;

	void CalculateGamePlayTime(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;
	//	void Release() override;

private:
	bool IsGameOver = false;
	bool IsGameClear = false;

	float TimeLimit = 180.0f;
	float CurrentPlayTime = 0.0f;

};

