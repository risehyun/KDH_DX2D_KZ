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


MainLevel2_3::MainLevel2_3()
{
}

MainLevel2_3::~MainLevel2_3()
{
}


void MainLevel2_3::Start()
{
#pragma region 레벨 효과음 로딩

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Sound\\FX\\PlayerFX\\");

	if (nullptr == GameEngineSound::FindSound("sound_slomo_disengage.wav"))
	{
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_disengage.wav"));
	}

	if (nullptr == GameEngineSound::FindSound("sound_slomo_engage.ogg"))
	{
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_engage.ogg"));
	}

#pragma endregion

	BaseLevel::InitCameraSetting();

	GameEngineInput::AddInputObject(this);

	FSM_Level_PlayGame();
	FSM_Level_SlowGame();
	FSM_Level_InitGame();
}

void MainLevel2_3::Update(float _Delta)
{
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
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 460.0f, -HalfWindowScale.Y - 240.0f });
		Object->GetMainRenderer()->LeftFlip();
		Object->GetMainRenderer()->ChangeAnimation("PreCrouch");
	}


	{
		std::shared_ptr<UITrigger> Object = CreateActor<UITrigger>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X - 320.0f, -HalfWindowScale.Y - 240.0f });
		Object->InitUITriggerData(TriggerType::StairIn);
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
		std::shared_ptr<UI_Mouse> Object = CreateActor<UI_Mouse>();
	}

	//{
	//	std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
	//	EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 300.0f, -HalfWindowScale.Y - 251.0f });
	//	EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
	//	EnemyObject->SetEnemyData(EnemyType::ShieldCop);
	//	EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
	//}

	//{
	//	std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
	//	EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 150.0f, -HalfWindowScale.Y - 251.0f });
	//	EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
	//	EnemyObject->SetEnemyData(EnemyType::Cop);
	//	EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
	//}

	//{
	//	std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
	//	EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 80.0f, -HalfWindowScale.Y - 251.0f });
	//	EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
	//	EnemyObject->SetEnemyData(EnemyType::ShotGunCop);
	//	EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
	//}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X + 20.0f, -HalfWindowScale.Y - 251.0f });
		EnemyObject->SetMapTexture("Map_MainLevel2_3.png");
		EnemyObject->SetEnemyData(EnemyType::ShotGunCop);
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
	}

	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->SetDoorType(EDoorType::Iron);
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 268.0f, -HalfWindowScale.Y + 40.0f });
	}

	//{
	//	std::shared_ptr<UI_PlayUI> UIObject = CreateActor<UI_PlayUI>();
	//	UIObject->UseHUD();
	//	UIObject->UseBattery();
	//	UIObject->UseItem();
	//	UIObject->UseTimer();
	//	UIObject->UseWeapon();
	//}

	//{
	//	std::shared_ptr<Portal> PortalObject = CreateActor<Portal>();
	//	PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4500.0f, -HalfWindowScale.Y - 250.0f });
	//	PortalObject->InitPortalData("TitleLevel", false);
	//}

	{
		//	CreateActor<SkyMap>();	
	}

	//Player::MainPlayer->SetMapTexture("Map_MainLevel1.png");

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

	LevelState.ChangeState(LevelState::InitGame);
}

void MainLevel2_3::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void MainLevel2_3::FSM_Level_PlayGame()
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

void MainLevel2_3::FSM_Level_SlowGame()
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

void MainLevel2_3::FSM_Level_InitGame()
{
	CreateStateParameter NewPara;

	NewPara.Start = [=](class GameEngineState* _Parent)
	{
		Player::MainPlayer->IsUseInput = false;

		PlayUI = CreateActor<UI_PlayUI>();
		PlayUI->UseHUD();
		PlayUI->OnGoArrow();
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
