#include "PreCompile.h"
#include "MainLevel2_4.h"

#include "Player.h"
#include "Enemy.h"

#include "Laser.h"
#include "LaserGroup.h"

#include "Door.h"
#include "GameStateManager.h"

#include "UI_Mouse.h"
#include "UI_PlayUI.h"

MainLevel2_4::MainLevel2_4()
{
}

MainLevel2_4::~MainLevel2_4()
{
}

void MainLevel2_4::Start()
{
	GameEngineInput::AddInputObject(this);

	BaseLevel::InitCameraSetting();


	FSM_Level_PlayGame();
	FSM_Level_SlowGame();
	FSM_Level_InitGame();
}

void MainLevel2_4::Update(float _Delta)
{

	CameraFocus(_Delta);

	LevelState.Update(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("BossLevel1_2");
	}
}

void MainLevel2_4::LevelStart(GameEngineLevel* _PrevLevel)
{
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
		// 2층 Object->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y });
		// 3층
		// Object->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y + 200.0f });

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
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 80.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::ShieldCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 180.0f, -HalfWindowScale.Y - 230.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop, EnemyDir::Left);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
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
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 426.0f, -HalfWindowScale.Y + 140.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_4.png");
		EnemyObject->SetEnemyData(EnemyType::Cop, EnemyDir::Right);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
	}

	// 3층 문
	{
		// ★ 문 초기 방향을 바꿀 수 있어야 함. 초기 방향 기준으로 충돌체와 위치 설정하도록 수정
		std::shared_ptr<Door> Object = CreateActor<Door>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X - 126.0f, -HalfWindowScale.Y + 134.0f });
		Object->SetDoorData(EDoorType::Iron, DoorDir::Left);
		Object->GetMainRenderer()->LeftFlip();
	}

	//{
	//	std::shared_ptr<Portal> PortalObject = CreateActor<Portal>();
	//	PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4500.0f, -HalfWindowScale.Y - 250.0f });
	//	PortalObject->InitPortalData("TitleLevel", false);
	//}


	{
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}


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

	NewPara.Init = [=](class GameEngineState* _Parent)
	{

	};

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		GameEngineCore::MainTime.SetGlobalTimeScale(1.0f);
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

		//if (GameEngineInput::IsUp(VK_LBUTTON, this))
		//{
		//	Player::MainPlayer->IsUseInput = true;
		//}



		if (true == Player::MainPlayer->GetPlayerDashable() ||
			GameEngineInput::IsDown(VK_LSHIFT, this))
		{
			SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_engage.ogg");
			SlowPlayer.SetVolume(0.3f);
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

	NewPara.End = [=](class GameEngineState* _Parent)
	{

	};

	LevelState.CreateState(LevelState::PlayGame, NewPara);
}

void MainLevel2_4::FSM_Level_SlowGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		GameEngineCore::MainTime.SetGlobalTimeScale(0.1f);
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
			SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_disengage.wav");
			SlowPlayer.SetVolume(1.0f);
			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}

		GameEngineCore::MainTime.SetGlobalTimeScale(0.1f);
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

void MainLevel2_4::FSM_Level_InitGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
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

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

	};

	LevelState.CreateState(LevelState::InitGame, NewPara);
}
