#include "PreCompile.h"
#include "MainLevel2_5.h"
#include "Player.h"
#include "UI_Mouse.h"
#include "UI_StageClear.h"
#include "Door.h"

MainLevel2_5::MainLevel2_5()
{
}

MainLevel2_5::~MainLevel2_5()
{
}

void MainLevel2_5::Start()
{

#pragma region ���� ȿ���� �ε�

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

void MainLevel2_5::Update(float _Delta)
{

	CameraFocus(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("BossLevel1_2");
	}

	LevelState.Update(_Delta);

}

void MainLevel2_5::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		StateManager = CreateActor<GameStateManager>();
		StateManager->InitEnemyTotalCount(static_cast<int>(AllSpawnedEnemy.size()));

	}

	{
		MapObject = CreateActor<Map>();

		MapObject->InitDebuggedMap("Map_MainLevel2_5_Origin.png", "Map_MainLevel2_5.png");
	}

	// 4�� ��
	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 640.0f, -HalfWindowScale.Y + 104.0f });
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Left);
		DoorObject->GetMainRenderer()->LeftFlip();
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 640.0f, -HalfWindowScale.Y + 104.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 3�� ��
	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 780.0f, -HalfWindowScale.Y - 184.0f });
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Right);
	}

	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X - 30.0f, -HalfWindowScale.Y - 184.0f });
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Left);
		DoorObject->GetMainRenderer()->LeftFlip();
	}

	// 3�� �߾� Enemy
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 580.0f, -HalfWindowScale.Y - 184.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 520.0f, -HalfWindowScale.Y - 184.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 160.0f, -HalfWindowScale.Y - 184.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 3�� ���� Enemy
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 820.0f, -HalfWindowScale.Y - 184.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 1200.0f, -HalfWindowScale.Y - 184.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 3�� ���� ��
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 500.0f, -HalfWindowScale.Y - 184.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 2�� ��
	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 610.0f, -HalfWindowScale.Y - 470.0f });
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Left);
		DoorObject->GetMainRenderer()->LeftFlip();
	}

	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 130.0f, -HalfWindowScale.Y - 470.0f });
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Left);
		DoorObject->GetMainRenderer()->LeftFlip();
	}

	// 2�� �߾� Enemy
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 580.0f, -HalfWindowScale.Y - 470.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 240.0f, -HalfWindowScale.Y - 470.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 2�� ���� Enemy
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 780.0f, -HalfWindowScale.Y - 470.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 2�� ���� Enemy
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 90.0f, -HalfWindowScale.Y - 470.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}


	// 1�� ��
	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 650.0f, -HalfWindowScale.Y - 730.0f });
		DoorObject->SetDoorData(EDoorType::Iron, DoorDir::Right);
	}

	// 1�� ���� Enemy
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 550.0f, -HalfWindowScale.Y - 730.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}

	// 1�� ���� Enemy
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 680.0f, -HalfWindowScale.Y - 730.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}



	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 840.0f, -HalfWindowScale.Y - 730.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllSpawnedEnemy.push_back(EnemyObject);
	}




	//{
	//	std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
	//	EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 326.0f, -HalfWindowScale.Y + 100.0f });
	//	EnemyObject->SetMapTexture("Map_MainLevel2_5.png");
	//	EnemyObject->SetEnemyData(EnemyType::FloorTurret, EnemyDir::Right);
	//	EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
	//	AllSpawnedEnemy.push_back(EnemyObject);
	//}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 1200.0f, -HalfWindowScale.Y + 104.0f });
		Object->GetMainRenderer()->LeftFlip();
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel2_5.png");

	{
		std::shared_ptr<UI_Mouse> Object = CreateActor<UI_Mouse>();
	}

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

void MainLevel2_5::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void MainLevel2_5::FSM_Level_PlayGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		GameEngineCore::MainTime.SetAllTimeScale(1.0f);
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		// �ʹݿ� ��� ������ �÷��̾��� �Է��� �����ϴ�.
		static float timer = 0.0f;

		timer += _Delta;

		if (timer > 2.0f && timer < 2.1f)
		{
			Player::MainPlayer->IsUseInput = true;
		}

		// �������� ���� �ð� �Ҹ� Ȯ���� ���� 10���
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
			PlayUI->OnGoArrowUI();
	//		StageTriggerObject->On();
		}
		else
		{

			PlayUI->OffGoArrowUI();

			if (nullptr != StageTriggerObject)
			{
				StageTriggerObject->Off();
			}

		}

		//// Ʈ���ſ� �浹�� ���÷��̷� �Ѿ�ϴ�
		//if (true == StageTriggerObject->GetPlayerDetect())
		//{
		//	LevelState.ChangeState(LevelState::ReplayGame);
		//	return;
		//}

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

void MainLevel2_5::FSM_Level_SlowGame()
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

		// 1�ʿ� �ѹ��� �ε����� �پ���.
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

			// Ÿ�̸� �ʱ�ȭ
			PressTimeControlTime = 0.0f;
		}
	};

	LevelState.CreateState(LevelState::SlowGame, NewPara);
}

void MainLevel2_5::FSM_Level_InitGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		LevelFxPlayer = GameEngineSound::SoundPlay("sound_level_start.wav");
		LevelFxPlayer.SetVolume(1.0f);

		Player::MainPlayer->IsUseInput = false;

		// �� HUD �ϳ��� �� ��� ó��
		PlayUI = CreateActor<UI_PlayUI>();
		PlayUI->UseHUD();
		PlayUI->UseBattery();
		PlayUI->UseItem();
		PlayUI->UseTimer();
		PlayUI->UseWeapon();

		PlayUI->GoArrow_UI->SetGoArrowData(float4::LEFT, { 50.0f, 480.0f });

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


			// Enemy�� �̹� �׾� �ִ� ��Ȳ�� ��, ���� ��忡�� �Ϲ� �����÷��̷� �Ѿ�鼭
			// �ٽ� Idle�� ���°� ����Ǵ� ���� ���� ���� �̹� �׾��ִ� ��쿡�� �������� �ʽ��ϴ�.
			if (false == AllSpawnedEnemy[i]->IsEnemyDeath)
			{
				AllSpawnedEnemy[i]->FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
			}
		}

		if (false == Player::MainPlayer->GetMainCollision()->GetUpdateValue())
		{
			Player::MainPlayer->GetMainCollision()->On();
		}

	//	DoorObject->ResetDoorState();

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

void MainLevel2_5::FSM_Level_ReplayGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		std::shared_ptr<UI_StageClear> UIObject = CreateActor<UI_StageClear>();
	//	StageTriggerObject->SetPlayerDetectOff();

		PlayUI->InactiveHUD();
		PlayUI->OffGoArrowUI();
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// Ʈ���� ���� �� ���̵��ξƿ� ó�� �� �ں��� ���÷��� ��� ����
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

void MainLevel2_5::FSM_Level_ReverseGame()
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

		// HUD ����
		// �ϱ׷��� ȿ��
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (false == GameStateManager::GameState->GetCurrentGameState())
		{

			// ���͸� �ʱ�ȭ
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


				// Enemy�� �̹� �׾� �ִ� ��Ȳ�� ��, ���� ��忡�� �Ϲ� �����÷��̷� �Ѿ�鼭
				// �ٽ� Idle�� ���°� ����Ǵ� ���� ���� ���� �̹� �׾��ִ� ��쿡�� �������� �ʽ��ϴ�.
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


		//	DoorObject->ResetDoorState();
			GameStateManager::GameState->ResetGamePlayTime();

			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}
	};

	LevelState.CreateState(LevelState::ReverseGame, NewPara);
}