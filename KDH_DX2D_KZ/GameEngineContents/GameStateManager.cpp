#include "PreCompile.h"
#include "GameStateManager.h"

// 타임 스케일, 게임 스테이트(IsGameOver), 
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
}

void GameStateManager::Update(float _Delta)
{
}
