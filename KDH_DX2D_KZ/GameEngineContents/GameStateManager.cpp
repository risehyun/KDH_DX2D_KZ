#include "PreCompile.h"
#include "GameStateManager.h"
#include "UI_PlayUI.h"

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
	// ���� �� �÷��� Ÿ���� �����Ͽ� ����մϴ�.
	CurrentPlayTime += _Delta;

	float TimeDecreaseAmount = 1 - CurrentPlayTime / TimeLimit;

	if (TimeDecreaseAmount >= 0.0f)
	{
		UI_PlayUI::PlayUI->SetTimerUIScale(TimeDecreaseAmount);
	}
}