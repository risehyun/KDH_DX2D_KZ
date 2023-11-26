#include "PreCompile.h"
#include "MainLevel2_3.h"

#include "Player.h"
#include "Enemy.h"

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

MainLevel2_3::MainLevel2_3()
{
}

MainLevel2_3::~MainLevel2_3()
{
}

void MainLevel2_3::Start()
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

	BaseLevel::InitCameraSetting();

	GameEngineInput::AddInputObject(this);

	FSM_Level_PlayGame();
	FSM_Level_SlowGame();
	FSM_Level_InitGame();
	FSM_Level_ReplayGame();
	FSM_Level_ReverseGame();
}

void MainLevel2_3::Update(float _Delta)
{
	CameraFocus(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("MainLevel2_4");
	}

	LevelState.Update(_Delta);
}

void MainLevel2_3::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 460.0f, -HalfWindowScale.Y - 240.0f });
		Object->GetMainRenderer()->LeftFlip();
		Object->GetMainRenderer()->ChangeAnimation("PreCrouch");
	}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_MainLevel2_3_Origin.png", "Map_MainLevel2_3.png");
	}

	{
		std::shared_ptr<WallHole> Object = CreateActor<WallHole>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 460.0f, -HalfWindowScale.Y - 200.0f });
	}

	{
		std::shared_ptr<FX_Explosion> Object = CreateActor<FX_Explosion>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 460.0f, -HalfWindowScale.Y - 180.0f });
	}

	{
		std::shared_ptr<FX_Explosion> Object = CreateActor<FX_Explosion>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 480.0f, -HalfWindowScale.Y - 215.0f });
	}

	{
		std::shared_ptr<FX_Explosion> Object = CreateActor<FX_Explosion>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 460.0f, -HalfWindowScale.Y - 230.0f });
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 300.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 150.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 80.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	//{
	//	std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
	//	EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 50.0f, -HalfWindowScale.Y - 230.0f });
	//	EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
	//	EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Right);
	//	EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
	//	AllSpawnedEnemy.push_back(EnemyObject);
	//}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y + 25.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 500.0f, -HalfWindowScale.Y + 25.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y + 25.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Right);
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 268.0f, -HalfWindowScale.Y + 40.0f });
	}

	{
		StageTriggerObject = CreateActor<UITrigger>();
		StageTriggerObject->InitUITriggerData(TriggerType::StageClear);
		StageTriggerObject->Transform.SetLocalPosition({ -30.0f, -HalfWindowScale.Y + 40.0f });
		StageTriggerObject->Off();
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel2_3.png");

	// Sound Setting
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

	{
		StateManager = CreateActor<GameStateManager>();
		StateManager->InitEnemyTotalCount(static_cast<int>(AllSpawnedEnemy.size()));
	}

	{
		std::shared_ptr<UI_Mouse> Object = CreateActor<UI_Mouse>();
	}

	LevelState.ChangeState(LevelState::InitGame);
}

void MainLevel2_3::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void MainLevel2_3::FSM_Level_PlayGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		for (size_t i = 0; i < AllSpawnedEnemy.size(); i++)
		{
			AllSpawnedEnemy[i]->IsUsingAutoPattern = true;
		}
		
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);

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
			AllSpawnedEnemy[i]->FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
		}

		StateManager->ResetLeftEnemyCount();

		if (false == Player::MainPlayer->GetMainCollision()->GetUpdateValue())
		{
			Player::MainPlayer->GetMainCollision()->On();
		}

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
			PlayUI->UIRenderer_GoArrow->Transform.SetWorldPosition({ 50.0f, 380.0f });
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

void MainLevel2_3::FSM_Level_SlowGame()
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

void MainLevel2_3::FSM_Level_InitGame()
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

void MainLevel2_3::FSM_Level_ReplayGame()
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
			GameEngineCore::ChangeLevel("MainLevel2_4");
		}
	};

	LevelState.CreateState(LevelState::ReplayGame, NewPara);
}

void MainLevel2_3::FSM_Level_ReverseGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		LevelFxPlayer = GameEngineSound::SoundPlay("sound_rewind.wav");
		LevelFxPlayer.SetVolume(1.0f);

		// HUD 제거
		// 일그러짐 효과
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (false == GameStateManager::GameState->GetCurrentGameState())
		{
			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}
	};

	LevelState.CreateState(LevelState::ReverseGame, NewPara);
}
