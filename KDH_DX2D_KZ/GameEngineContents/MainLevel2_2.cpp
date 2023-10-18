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
	// ★ 상위 레벨 클래스로 옮기기
	{
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
	}
}

void MainLevel2_2::Update(float _Delta)
{
	if (GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainLevel2_3");
	}

	static float PressTime = 0.0f;
	static float FreeTime = 0.0f;
	static int   CurBatteryIndex = -1;

	// ★ PlayLevel이라는 상위 클래스에서 가지고 있는 게 좋을 것 같다.
	// LSHIFT키를 누르고 있을 때는 일정 시간 간격으로 배터리 칸이 1씩 사라지고,
	// 뗐을 때는 반대로 일정 시간 간격으로 배터리 칸이 1씩 늘어난다.
	// 배터리 칸이 0일 때는 시간 조작을 사용할 수 없다. (대쉬 포함)


	if (true == GameEngineInput::IsDown(VK_LSHIFT))
	{
		SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_engage.ogg");
		SlowPlayer.SetVolume(0.3f);
	}

	// 스위치문 사용하면 될 것 같은데
	else if (GameEngineInput::IsPress(VK_LSHIFT))
	{
		CurBatteryIndex = -1;

		//FreeTime = 0.0f;

		GameEngineCore::MainTime.SetGlobalTimeScale(0.5f);
		PressTime += _Delta;

		if (PressTime > 14.0f)
		{
			CurBatteryIndex = 0;
			return;
		}

		if (PressTime > 1.0f)
		{
			CurBatteryIndex = 11;
		}

		if (PressTime > 2.0f)
		{
			CurBatteryIndex = 10;
		}

		if (PressTime > 3.0f)
		{
			CurBatteryIndex = 9;
		}

		if (PressTime > 4.0f)
		{
			CurBatteryIndex = 8;
		}

		if (PressTime > 5.0f)
		{
			CurBatteryIndex = 7;
		}

		if (PressTime > 6.0f)
		{
			CurBatteryIndex = 6;
		}

		if (PressTime > 7.0f)
		{
			CurBatteryIndex = 5;
		}

		if (PressTime > 8.0f)
		{
			CurBatteryIndex = 4;
		}

		if (PressTime > 9.0f)
		{
			CurBatteryIndex = 3;
		}

		if (PressTime > 10.0f)
		{
			CurBatteryIndex = 2;
		}

		if (PressTime > 11.0f)
		{
			CurBatteryIndex = 1;
		}

		if (PressTime > 13.0f)
		{
			CurBatteryIndex = 0;
		}

		if (CurBatteryIndex != -1 &&
			true == PlayUIObject->UIRenderer_BatteryParts[CurBatteryIndex]->GetUpdateValue())
		{
			PlayUIObject->OffBatteryParts(CurBatteryIndex);
		}

	}

	// 버튼을 떼고 있는 상태에서는 가장 마지막에 있었던 위치 이후부터 한칸씩 정상화 되어야 한다.
	// 즉, 인덱스가 필요하다.
	// 다시 채울 때 인덱스는 시간이 지남에 따라 하나씩 늘어나야 한다.
	// 이때 인덱스는 최대값인 11을 넘어설 수 없다.

	else if (GameEngineInput::IsUp(VK_LSHIFT))
	{
		SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_disengage.wav");
		SlowPlayer.SetVolume(1.0f);
	}

	else if (GameEngineInput::IsFree(VK_LSHIFT))
	{


		PressTime = 0.0f;
		GameEngineCore::MainTime.SetGlobalTimeScale(1.0f);

		if (CurBatteryIndex != -1)
		{
			FreeTime += _Delta / 2;
		}

		if (CurBatteryIndex != -1 &&
			PlayUIObject != nullptr)
		{
//			int tempIndex = CurBatteryIndex;

			if (FreeTime > 1.0f)
			{
				if (CurBatteryIndex > 11)
				{
					CurBatteryIndex = 11;
				}

				if (false == PlayUIObject->UIRenderer_BatteryParts[CurBatteryIndex]->GetUpdateValue())
				{
					PlayUIObject->OnBatteryParts(CurBatteryIndex);
				}

				++CurBatteryIndex;
				FreeTime = 0.0f;
			}

//
//			for (int i = CurBatteryIndex; i < 12; i++)
//			{
//				//if (FreeTime > 1.0f)
//				//{
//					PlayUIObject->OnBatteryParts(i);
////				}
//
//			//	FreeTime = 0.0f;
//
//			}

			
		}
//		}

	//	CurBatteryIndex = -1;

	}

	UpdateLevelState(_Delta);
}

void MainLevel2_2::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ HalfWindowScale.X, 300, -500.0f });

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

	ChangeLevelState(ELevelState::Intro);
}

void MainLevel2_2::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void MainLevel2_2::ChangeLevelState(ELevelState _NextLevelState)
{
	LevelState = _NextLevelState;

	switch (LevelState)
	{
	case ELevelState::Intro:
		FSM_Intro_Start();
		break;

	case ELevelState::StartGame:
		FSM_StartGame_Start();
		break;

	case ELevelState::Default:
	default:
		break;

	}
}

void MainLevel2_2::UpdateLevelState(float _Delta)
{
	switch (LevelState)
	{
	case ELevelState::Intro:
		FSM_Intro_Update(_Delta);
		break;

	case ELevelState::StartGame:
		FSM_StartGame_Update(_Delta);
		break;

	case ELevelState::Default:
	default:
		break;
	}
}

void MainLevel2_2::FSM_Intro_Start()
{
	Player::MainPlayer->IsUseInput = false;
}

void MainLevel2_2::FSM_StartGame_Start()
{
	PlayUIObject = CreateActor<UI_PlayUI>();
	PlayUIObject->UseHUD();
	PlayUIObject->OnGoArrow();
//Player::MainPlayer->IsUseInput = true;
}

void MainLevel2_2::FSM_Intro_Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeLevelState(ELevelState::StartGame);
	}
}

void MainLevel2_2::FSM_StartGame_Update(float _Delta)
{

	static float timer = 0.0f;

	timer += _Delta;

	if (timer > 1.0f && timer < 1.1f)
	{
		Player::MainPlayer->IsUseInput = true;
	}
}
