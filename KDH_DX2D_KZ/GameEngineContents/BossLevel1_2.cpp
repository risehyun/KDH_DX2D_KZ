#include "PreCompile.h"
#include "BossLevel1_2.h"
#include "GameStateManager.h"
#include "Player.h"
#include "UI_Mouse.h"

#include "Boss.h"
#include "Enemy.h"
#include "WallOpen.h"

// 테스트용
#include "BossSmoke.h"
#include "UI_StageClear.h"

#include "BossLaser.h"


BossLevel1_2::BossLevel1_2()
{
}

BossLevel1_2::~BossLevel1_2()
{
}

void BossLevel1_2::Start()
{
	GameEngineInput::AddInputObject(this);

	BaseLevel::InitCameraSetting();

	FSM_Level_PlayGame();
	FSM_Level_SlowGame();
	FSM_Level_InitGame();
	FSM_Level_ReverseGame();
	FSM_Level_ReplayGame();
}

void BossLevel1_2::Update(float _Delta)
{
	CameraFocus(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}

	LevelState.Update(_Delta);
}

void BossLevel1_2::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	{
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_BossLevel1_2_Origin.png", "Map_BossLevel1_2.png");
	}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		// 시작 지점
		Object->Transform.SetLocalPosition({ HalfWindowScale.X - 280.0f, -HalfWindowScale.Y - 150.0f });

		Object->GetMainRenderer()->RightFlip();
	}

	{

		MainBoss = CreateActor<Boss>();
		MainBoss->Transform.SetLocalPosition({ HalfWindowScale.X + 280.0f, -HalfWindowScale.Y - 150.0f });
		MainBoss->GetMainRenderer()->LeftFlip();
		MainBoss->SetMapTexture("Map_BossLevel1_2.png");

	}

	{
		std::shared_ptr<UI_Mouse> Object = CreateActor<UI_Mouse>();
	}

	Player::MainPlayer->SetMapTexture("Map_BossLevel1_2.png");


	{
		StageTriggerObject = CreateActor<UITrigger>();
		StageTriggerObject->InitUITriggerData(TriggerType::StageClear);
		StageTriggerObject->Off();
	}



	{
		std::shared_ptr<BossSmoke> Object = CreateActor<BossSmoke>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 200.0f, -HalfWindowScale.Y - 150.0f });
	}


	if (nullptr == GameEngineSound::FindSound("song_fullconfession.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_fullconfession.ogg"));
	}

	BGMPlayer = GameEngineSound::SoundPlay("song_fullconfession.ogg", 5);
	BGMPlayer.SetVolume(0.3f);

	LevelState.ChangeState(LevelState::InitGame);
}

void BossLevel1_2::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void BossLevel1_2::FSM_Level_PlayGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{			
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (true == GameStateManager::GameState->GetCurrentGameState())
		{
			GameEngineCore::MainTime.SetAllTimeScale(0.0f);
			LevelState.ChangeState(LevelState::ReverseGame);
			return;
		}

		if (true == MainBoss->GetBossDeath())
		{
			static float Timer = 0.0f;

			Timer += _Delta;


			if (Timer > 2.0f)
			{
				float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
				StageTriggerObject->On();
				StageTriggerObject->Transform.SetLocalPosition({ HalfWindowScale.X - 280.0f, -HalfWindowScale.Y - 150.0f });
				StageTriggerObject->SetMainCollisionScale({ 1000.0f, 1000.0f });;

				Boss::Boss_HeadHunter->SetBossDeathOff();
				LevelState.ChangeState(LevelState::ReplayGame);
				return;
			}
		}

		// 초반에 잠시 동안은 플레이어의 입력을 막습니다.
		static float timer = 0.0f;

		timer += _Delta;

		if (timer > 2.0f && timer < 2.1f)
		{
			Player::MainPlayer->IsUseInput = true;
		}

		if (true == Player::MainPlayer->GetPlayerDashable() ||
			GameEngineInput::IsDown(VK_LSHIFT, this))
		{
			LevelFxPlayer = GameEngineSound::SoundPlay("sound_slomo_engage.ogg");
			LevelFxPlayer.SetVolume(0.3f);
			_Parent->ChangeState(LevelState::SlowGame);
			return;
		}

		PressTimeControlTime = 0.0f;
		GameEngineCore::MainTime.SetGlobalTimeScale(1.0f);

		FreeTimeControlTime += _Delta / 2;

		if (PlayUI != nullptr)
		{
			if (FreeTimeControlTime > 1.0f)
			{
				if (GameStateManager::GameState->CurTimeControlBattery >= 11)
				{
					GameStateManager::GameState->CurTimeControlBattery = 11;
					return;
				}
				else
				{
					++GameStateManager::GameState->CurTimeControlBattery;

					PlayUI->OnBatteryParts(GameStateManager::GameState->CurTimeControlBattery);

				}

				FreeTimeControlTime = 0.0f;
			}
		}


	};

	LevelState.CreateState(LevelState::PlayGame, NewPara);
}

void BossLevel1_2::FSM_Level_SlowGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		GameEngineCore::MainTime.SetAllTimeScale(0.1f);
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (GameStateManager::GameState->CurTimeControlBattery < 0)
		{
			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}

		if (GameEngineInput::IsUp(VK_LSHIFT, this) ||
			false == Player::MainPlayer->GetPlayerDashable() && GameEngineInput::IsFree(VK_LSHIFT, this))
		{
			LevelFxPlayer = GameEngineSound::SoundPlay("sound_slomo_disengage.wav");
			LevelFxPlayer.SetVolume(1.0f);
			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}


		GameEngineCore::MainTime.SetAllTimeScale(0.1f);
		PressTimeControlTime += (_Delta * 5.0f);

		// 1초에 한번씩 인덱스가 줄어든다.
		if (PressTimeControlTime > 1.0f)
		{
			if (GameStateManager::GameState->CurTimeControlBattery >= 0)
			{
				if (true == PlayUI->UIRenderer_BatteryParts[GameStateManager::GameState->CurTimeControlBattery]->GetUpdateValue())
				{
					PlayUI->OffBatteryParts(GameStateManager::GameState->CurTimeControlBattery);
				}

				--GameStateManager::GameState->CurTimeControlBattery;
			}
			else
			{
				return;
			}

			// 타이머 초기화
			PressTimeControlTime = 0.0f;
		}
	};

	LevelState.CreateState(LevelState::SlowGame, NewPara);
}

void BossLevel1_2::FSM_Level_InitGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		LevelFxPlayer = GameEngineSound::SoundPlay("sound_level_start.wav");
		LevelFxPlayer.SetVolume(1.0f);

		Player::MainPlayer->IsUseInput = false;

		PlayUI = CreateActor<UI_PlayUI>();
		PlayUI->UseHUD();
		PlayUI->UseBattery();
		PlayUI->UseItem();
		PlayUI->UseTimer();
		PlayUI->UseWeapon();

		LevelState.ChangeState(LevelState::PlayGame);
		return;
	};

	LevelState.CreateState(LevelState::InitGame, NewPara);
}

void BossLevel1_2::FSM_Level_ReverseGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);

		if (nullptr != Boss::Boss_HeadHunter->KnifeItem)
		{
			Boss::Boss_HeadHunter->KnifeItem->Death();
		}

		LevelFxPlayer = GameEngineSound::SoundPlay("sound_rewind.wav");
		LevelFxPlayer.SetVolume(1.0f);
		MainBoss->ResetBossHp();
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (false == GameStateManager::GameState->GetCurrentGameState())
		{
			if (false == Player::MainPlayer->GetMainCollision()->GetUpdateValue())
			{
				Player::MainPlayer->GetMainCollision()->On();
			}

			GameStateManager::GameState->ResetGamePlayTime();

			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}
	};

	LevelState.CreateState(LevelState::ReverseGame, NewPara);
}

void BossLevel1_2::FSM_Level_ReplayGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		StageTriggerObject->SetPlayerDetectOff();

		PlayUI->InactiveHUD();
		PlayUI->OffGoArrow();
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// 트리거 진입 후 페이드 처리가 끝나면 레벨 변경
		if (LevelState.GetStateTime() > 2.0f
			&& false == GameStateManager::GameState->GetCurrentGameClear())
		{
			if (StageEndFadeObject == nullptr)
			{
				StageEndFadeObject = CreateActor<UI_FadeObject>();
				StageEndFadeObject->SetFadeObjectType(EFadeObjectType::Background);
				StageEndFadeObject->SwitchFadeMode(1);
			}

		}

		if (StageEndFadeObject != nullptr && true == StageEndFadeObject->IsEnd)
		{
			GameEngineCore::ChangeLevel("EndingLevel");
		}
	};

	LevelState.CreateState(LevelState::ReplayGame, NewPara);


}