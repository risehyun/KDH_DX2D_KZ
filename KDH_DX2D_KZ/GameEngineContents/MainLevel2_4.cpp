#include "PreCompile.h"
#include "MainLevel2_4.h"

#include "Player.h"
#include "Enemy.h"

#include "Laser.h"
#include "LaserGroup.h"

#include "UI_Mouse.h"
#include "UI_PlayUI.h"

#include "Door.h"
#include "WallHole.h"
#include "FX_Explosion.h"
#include "UITrigger.h"
#include "GameStateManager.h"
#include "Portal.h"
#include "UI_FadeObject.h"

// 테스트용
#include "UI_StageClear.h"

MainLevel2_4::MainLevel2_4()
{
}

MainLevel2_4::~MainLevel2_4()
{
}

void MainLevel2_4::Start()
{
#pragma region 레벨 효과음 로딩

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\FX\\LevelFX\\");

		if (nullptr == GameEngineSound::FindSound("sound_slomo_disengage.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_disengage.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_slomo_engage.ogg"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_engage.ogg"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_rewind.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_rewind.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_level_start.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_level_start.wav"));
		}
	}

#pragma endregion


	GameEngineInput::AddInputObject(this);

	BaseLevel::InitCameraSetting();

	FSM_Level_PlayGame();
	FSM_Level_SlowGame();
	FSM_Level_InitGame();
	FSM_Level_ReplayGame();
	FSM_Level_ReverseGame();



}

void MainLevel2_4::Update(float _Delta)
{

	CameraFocus(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("BossLevel1_2");
	}

	LevelState.Update(_Delta);

}

void MainLevel2_4::LevelStart(GameEngineLevel* _PrevLevel)
{
#pragma region 레벨 오브젝트 생성
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_MainLevel2_4_Origin.png", "Map_MainLevel2_4.png");
	}

	{
		std::shared_ptr<UI_Mouse> Object = CreateActor<UI_Mouse>();
	}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		// 1층 시작 지점
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y - 480.0f });
		Object->GetMainRenderer()->LeftFlip();
	}


	// 1층 레이저-> x축 기준 60씩 차이
	{
		std::shared_ptr<LaserGroup> Object = CreateActor<LaserGroup>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 43.0f, -HalfWindowScale.Y - 438.0f });
		Object->InitLaserGroupData(6, { HalfWindowScale.X + 43.0f, -HalfWindowScale.Y - 438.0f }, 60.0f, false, false);
	}

	// 2층 레이저 -> x축 기준 196씩 차이
	{
		std::shared_ptr<LaserGroup> Object = CreateActor<LaserGroup>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 382.0f, -HalfWindowScale.Y - 80.0f });
		Object->InitLaserGroupData(2, { HalfWindowScale.X + 382.0f, -HalfWindowScale.Y - 80.0f }, 196.0f, true, false);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 326.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 80.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 180.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 3층 레이저 -> x축 기준 62씩 차이
	{
		std::shared_ptr<LaserGroup> Object = CreateActor<LaserGroup>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 144.0f, -HalfWindowScale.Y + 170.0f });
		Object->InitLaserGroupData(3, { HalfWindowScale.X + 10.0f, -HalfWindowScale.Y + 170.0f }, 62.0f, false, true);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 326.0f, -HalfWindowScale.Y + 100.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::FloorTurret, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 426.0f, -HalfWindowScale.Y + 140.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 3층 문
	{
		DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X - 126.0f, -HalfWindowScale.Y + 134.0f });
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Left);
		DoorObject->GetMainRenderer()->LeftFlip();
	}

	{
		StateManager = CreateActor<GameStateManager>();
		StateManager->InitEnemyTotalCount(static_cast<int>(AllSpawnedEnemy.size()));

	}

	{
		StageTriggerObject = CreateActor<UITrigger>();
		StageTriggerObject->InitUITriggerData(TriggerType::StageClear);
		StageTriggerObject->Transform.SetLocalPosition({ -30.0f, -HalfWindowScale.Y + 100.0f });
		StageTriggerObject->Off();
	}
#pragma endregion

	Player::MainPlayer->SetMapTexture("Map_MainLevel2_4.png");

	if (nullptr == GameEngineSound::FindSound("song_dragon.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_dragon.ogg"));
	}

	BGMPlayer = GameEngineSound::SoundPlay("song_dragon.ogg", 5);
	BGMPlayer.SetVolume(0.3f);

	LevelState.ChangeState(LevelState::InitGame);
}

void MainLevel2_4::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void MainLevel2_4::FSM_Level_PlayGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		// 초반에 잠시 동안은 플레이어의 입력을 막습니다.
		static float timer = 0.0f;

		timer += _Delta;

		if (timer > 2.0f && timer < 2.1f)
		{
			Player::MainPlayer->IsUseInput = true;
		}

		// 스테이지 제한 시간 소모 확인을 위해 10배속
		if (true == GameEngineInput::IsPress(VK_CONTROL, this))
		{
			GameEngineCore::MainTime.SetAllTimeScale(10.0f);
		}

		if (true == GameStateManager::GameState->GetCurrentGameState())
		{
			LevelState.ChangeState(LevelState::ReverseGame);
			return;
		}

		if (GameStateManager::GameState->LeftEnemy <= 0)
		{
			PlayUI->UIRenderer_GoArrow->Transform.SetWorldPosition({ 50.0f, 480.0f });
			PlayUI->SetGoArrowLeft();
			PlayUI->OnGoArrow();
			StageTriggerObject->On();
		}
		else
		{
			if (true == PlayUI->UIRenderer_GoArrow->GetUpdateValue())
			{
				PlayUI->OffGoArrow();
			}

			if (nullptr != StageTriggerObject)
			{
				StageTriggerObject->Off();
			}

		}

		// 트리거와 충돌시 리플레이로 넘어갑니다
		if (true == StageTriggerObject->GetPlayerDetect())
		{
			LevelState.ChangeState(LevelState::ReplayGame);
			return;
		}

		if (true == Player::MainPlayer->GetPlayerDashable() ||
			GameEngineInput::IsDown(VK_LSHIFT, this))
		{
			LevelFxPlayer = GameEngineSound::SoundPlay("sound_slomo_engage.ogg");
			LevelFxPlayer.SetVolume(1.0f);
			_Parent->ChangeState(LevelState::SlowGame);
			return;
		}

		PressTimeControlTime = 0.0f;

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

void MainLevel2_4::FSM_Level_SlowGame()
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
		PressTimeControlTime += _Delta;

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

void MainLevel2_4::FSM_Level_InitGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		LevelFxPlayer = GameEngineSound::SoundPlay("sound_level_start.wav");
		LevelFxPlayer.SetVolume(1.0f);

		Player::MainPlayer->IsUseInput = false;

		// ★ HUD 하나로 다 묶어서 처리
		PlayUI = CreateActor<UI_PlayUI>();
		PlayUI->UseHUD();
		PlayUI->UseBattery();
		PlayUI->UseItem();
		PlayUI->UseTimer();
		PlayUI->UseWeapon();

		StageStartFadeObject = CreateActor<UI_FadeObject>();
		StageStartFadeObject->SetFadeObjectType(EFadeObjectType::Background);
		StageStartFadeObject->SwitchFadeMode(0);

		for (size_t i = 0; i < AllSpawnedEnemy.size(); i++)
		{
			AllSpawnedEnemy[i]->IsUsingAutoPattern = true;
		}

		for (size_t i = 0; i < AllSpawnedEnemy.size(); i++)
		{
			if (false == AllSpawnedEnemy[i]->GetMainCollision()->GetUpdateValue())
			{
				AllSpawnedEnemy[i]->GetMainCollision()->On();
			}

			if (false == AllSpawnedEnemy[i]->EnemyDetectCollision->GetUpdateValue())
			{
				AllSpawnedEnemy[i]->EnemyDetectCollision->On();
			}

			AllSpawnedEnemy[i]->ResetDir();


			// Enemy가 이미 죽어 있는 상황일 때, 슬로 모드에서 일반 게임플레이로 넘어가면서
			// 다시 Idle로 상태가 변경되는 것을 막기 위해 이미 죽어있는 경우에는 변경하지 않습니다.
			if (false == AllSpawnedEnemy[i]->IsEnemyDeath)
			{
				AllSpawnedEnemy[i]->FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
			}
		}

		if (false == Player::MainPlayer->GetMainCollision()->GetUpdateValue())
		{
			Player::MainPlayer->GetMainCollision()->On();
		}

		DoorObject->ResetDoorState();

	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (true == StageStartFadeObject->IsEnd)
		{
			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}

	};

	LevelState.CreateState(LevelState::InitGame, NewPara);
}

void MainLevel2_4::FSM_Level_ReplayGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		std::shared_ptr<UI_StageClear> UIObject = CreateActor<UI_StageClear>();
		StageTriggerObject->SetPlayerDetectOff();

		PlayUI->InactiveHUD();
		PlayUI->OffGoArrow();
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// 트리거 진입 후 페이드인아웃 처리 된 뒤부터 리플레이 재생 시작
		if (LevelState.GetStateTime() > 2.2f
			&& false == GameStateManager::GameState->GetCurrentGameClear())
		{
			GameStateManager::GameState->SetGameClearOn();

			if (false == PlayUI->Get_UIGameReplay()->GetUpdateValue())
			{
				PlayUI->Set_UIGameReplay_On();
			}
		}

		if (GameEngineInput::IsDown(VK_RBUTTON, this))
		{
			PlayUI->Set_UIGameReplay_Off();
			StageEndFadeObject = CreateActor<UI_FadeObject>();
			StageEndFadeObject->SetFadeObjectType(EFadeObjectType::Background);
			StageEndFadeObject->SwitchFadeMode(1);
		}

		if (StageEndFadeObject != nullptr && true == StageEndFadeObject->IsEnd)
		{
			GameEngineCore::ChangeLevel("BossLevel1_2");
		}
	};

	LevelState.CreateState(LevelState::ReplayGame, NewPara);
}

void MainLevel2_4::FSM_Level_ReverseGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{

		GameEngineCore::MainTime.SetAllTimeScale(1.0f);

		for (size_t i = 0; i < AllSpawnedEnemy.size(); i++)
		{
			if (true == AllSpawnedEnemy[i]->EnemyDetectCollision->GetUpdateValue())
			{
				AllSpawnedEnemy[i]->EnemyDetectCollision->Off();
			}
		}


		LevelFxPlayer = GameEngineSound::SoundPlay("sound_rewind.wav");
		LevelFxPlayer.SetVolume(1.0f);

		// HUD 제거
		// 일그러짐 효과
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (false == GameStateManager::GameState->GetCurrentGameState())
		{

			// 배터리 초기화
			GameStateManager::GameState->ResetTimeControlBattery();

			int InitIndex = GameStateManager::GameState->GetCurTimeControlBattery();

			for (int i = 0; i <= InitIndex; i++)
			{
				PlayUI->OnBatteryParts(i);
			}

			for (size_t i = 0; i < AllSpawnedEnemy.size(); i++)
			{

				AllSpawnedEnemy[i]->IsUsingAutoPattern = true;
				AllSpawnedEnemy[i]->IsEnemyDeath = false;
				AllSpawnedEnemy[i]->FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);

				if (false == AllSpawnedEnemy[i]->GetMainCollision()->GetUpdateValue())
				{
					AllSpawnedEnemy[i]->GetMainCollision()->On();
				}

				if (false == AllSpawnedEnemy[i]->EnemyDetectCollision->GetUpdateValue())
				{
					AllSpawnedEnemy[i]->EnemyDetectCollision->On();
				}

				AllSpawnedEnemy[i]->ResetDir();


				// Enemy가 이미 죽어 있는 상황일 때, 슬로 모드에서 일반 게임플레이로 넘어가면서
				// 다시 Idle로 상태가 변경되는 것을 막기 위해 이미 죽어있는 경우에는 변경하지 않습니다.
				if (false == AllSpawnedEnemy[i]->IsEnemyDeath)
				{
					AllSpawnedEnemy[i]->FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
				}
			}

			if (false == Player::MainPlayer->GetMainCollision()->GetUpdateValue())
			{
				Player::MainPlayer->GetMainCollision()->On();
			}

			StateManager->ResetLeftEnemyCount();


			DoorObject->ResetDoorState();
			GameStateManager::GameState->ResetGamePlayTime();

			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}
	};

	LevelState.CreateState(LevelState::ReverseGame, NewPara);
}