#include "PreCompile.h"
#include "GameStateManager.h"
#include "UI_PlayUI.h"
#include "Player.h"

// 타임 스케일, 게임 스테이트(IsGameOver), 
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
	// 현재 총 플레이 타임을 누적하여 계산합니다.
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
	// 조건 변경 해줘야 한다.
	if (false == Player::MainPlayer->IsRecordPlayMode
		&& false == Player::MainPlayer->GetMainRenderer()->IsCurAnimation("Death"))
	{
		// 현재 총 플레이 타임을 누적하여 계산합니다.
		CalculateGamePlayTime(_Delta);
	}
}