#include "PreCompile.h"
#include "GameStateManager.h"

// Ÿ�� ������, ���� ������Ʈ(IsGameOver), 
GameStateManager* GameStateManager::GameState = nullptr;

GameStateManager::GameStateManager()
{
	GameState = this;
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::Start()
{
	CurTimeControlBattery = MaxTimeControlBattery;
}

void GameStateManager::Update(float _Delta)
{
}
