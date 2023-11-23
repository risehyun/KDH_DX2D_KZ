#include "PreCompile.h"
#include "GameStateManager.h"
#include "UI_PlayUI.h"
#include "Player.h"

// Ÿ�� ������, ���� ������Ʈ(IsGameOver), 
GameStateManager* GameStateManager::GameState = nullptr;

GameStateManager::GameStateManager()
{
	GameState = this;
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::CalculateGamePlayTime(float _Delta)
{
	// ���� �� �÷��� Ÿ���� �����Ͽ� ����մϴ�.
	CurrentPlayTime += _Delta;

	float TimeDecreaseAmount = 1.0f - CurrentPlayTime / TimeLimit;

	if (TimeDecreaseAmount >= 0.0f)
	{
		UI_PlayUI::PlayUI->SetTimerUIScale(TimeDecreaseAmount);
	}
}

void GameStateManager::Start()
{
	CurTimeControlBattery = MaxTimeControlBattery;
}

void GameStateManager::Update(float _Delta)
{
	// ���� ���� ����� �Ѵ�.
	if (false == Player::MainPlayer->IsRecordPlayMode
		&& false == Player::MainPlayer->GetMainRenderer()->IsCurAnimation("Death"))
	{
		// ���� �� �÷��� Ÿ���� �����Ͽ� ����մϴ�.
		CalculateGamePlayTime(_Delta);
	}
}