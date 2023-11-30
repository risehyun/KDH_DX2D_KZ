#include "PreCompile.h"
#include "MainLevel2_2.h"
#include "Player.h"
#include "SkyMap.h"
#include "Portal.h"

#include "UI_Mouse.h"
#include "UI_StageName.h"
#include "UI_NowPlayingSong.h"
#include "PinPointLight.h"

#include "GameStateManager.h"

MainLevel2_2::MainLevel2_2()
{
}

MainLevel2_2::~MainLevel2_2()
{
}

void MainLevel2_2::Start()
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

	FSM_Level_InitGame();
	FSM_Level_PlayGame();
	FSM_Level_SlowGame();

}

void MainLevel2_2::Update(float _Delta)
{
	CameraFocus(_Delta);

	LevelState.Update(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("MainLevel2_3");
	}




}

void MainLevel2_2::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	{
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X - 450.0f, -HalfWindowScale.Y - 200.0f });
	}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_MainLevel2_2_Origin.png", "Map_MainLevel2_2.png");
	}

	{
		std::shared_ptr<UI_Mouse> MouseObject = CreateActor<UI_Mouse>();
	}

	{
		std::shared_ptr<Portal> PortalObject = CreateActor<Portal>();
		PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 2500.0f, -HalfWindowScale.Y - 200.0f });
		PortalObject->InitPortalData("MainLevel2_3", false);
	}

	{
		std::shared_ptr<SkyMap> SkyMapObject = CreateActor<SkyMap>();
		SkyMapObject->SetSkyMapType(ESkyType::PrisonSky);
	}

	{
		std::shared_ptr<PinPointLight> LightObject = CreateActor<PinPointLight>();
		LightObject->Transform.SetLocalPosition({ HalfWindowScale.X - 150.0f, -HalfWindowScale.Y + 90.0f });
		LightObject->InitRotationDir(ERotationDir::Right);
	}

	{
		std::shared_ptr<PinPointLight> LightObject = CreateActor<PinPointLight>();
		LightObject->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y + 90.0f });
		LightObject->InitRotationDir(ERotationDir::Left);
	}

	{
		std::shared_ptr<PinPointLight> LightObject = CreateActor<PinPointLight>();
		LightObject->Transform.SetLocalPosition({ HalfWindowScale.X + 1500.0f, -HalfWindowScale.Y + 90.0f });
		LightObject->InitRotationDir(ERotationDir::Right);
	}

	{
		std::shared_ptr<UI_StageName> StageNameObejct = CreateActor<UI_StageName>();
		StageNameObejct->InitStageNameData(EStageNameType::Prison);
	}

	{
		std::shared_ptr<UI_NowPlayingSong> StageNameObejct = CreateActor<UI_NowPlayingSong>();
	}

	Player::MainPlayer->SetMapTexture("Map_MainLevel2_2.png");

	// Sound Setting
	if (nullptr == GameEngineSound::FindSound("song_thirddistrict.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_thirddistrict.ogg"));
	}

	BGMPlayer.SetVolume(0.3f);
	BGMPlayer = GameEngineSound::SoundPlay("song_thirddistrict.ogg", 5);

	LevelState.ChangeState(LevelState::InitGame);

}

void MainLevel2_2::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void MainLevel2_2::FSM_Level_InitGame()
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

void MainLevel2_2::FSM_Level_PlayGame()
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

void MainLevel2_2::FSM_Level_SlowGame()
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
