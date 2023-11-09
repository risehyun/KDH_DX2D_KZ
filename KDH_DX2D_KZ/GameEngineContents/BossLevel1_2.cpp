#include "PreCompile.h"
#include "BossLevel1_2.h"
#include "GameStateManager.h"
#include "Player.h"
#include "UI_Mouse.h"

#include "Boss.h"
#include "Enemy.h"
#include "WallOpen.h"

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
}

void BossLevel1_2::Update(float _Delta)
{
	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}
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

	//{
	//	std::shared_ptr<WallOpen> Object = CreateActor<WallOpen>();
	//	Object->Transform.SetLocalPosition({ HalfWindowScale.X - 468.0f, -HalfWindowScale.Y - 30.0f });
	//}

	//{
	//	std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
	//	EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 426.0f, -HalfWindowScale.Y - 70.0f });
	//	EnemyObject->SetMapTexture("Map_BossLevel1_2.png");
	//	EnemyObject->SetEnemyData(EnemyType::WallTurret, EnemyDir::Right);
	//	EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
	//}

	//{
	//	std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
	//	EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 426.0f, -HalfWindowScale.Y + 30.0f });
	//	EnemyObject->SetMapTexture("Map_BossLevel1_2.png");
	//	EnemyObject->SetEnemyData(EnemyType::WallTurret, EnemyDir::Right);
	//	EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
	//}

	{
		std::shared_ptr<Boss> Object = CreateActor<Boss>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 280.0f, -HalfWindowScale.Y - 150.0f });
		Object->GetMainRenderer()->LeftFlip();
		Object->SetMapTexture("Map_BossLevel1_2.png");

	}


	{
		std::shared_ptr<UI_Mouse> Object = CreateActor<UI_Mouse>();
	}


	Player::MainPlayer->SetMapTexture("Map_BossLevel1_2.png");
	


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

void BossLevel1_2::FSM_Level_SlowGame()
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

void BossLevel1_2::FSM_Level_InitGame()
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
	};

	NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (GameEngineInput::IsDown(VK_LBUTTON, this))
		{
			LevelState.ChangeState(LevelState::PlayGame);
			return;
		}
	};

	LevelState.CreateState(LevelState::InitGame, NewPara);
}
