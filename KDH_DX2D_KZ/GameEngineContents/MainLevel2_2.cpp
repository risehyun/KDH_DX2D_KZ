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
	GameEngineInput::AddInputObject(this);

	// �� ���� ���� Ŭ������ �ű��
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

	// PlayGame
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
				if (GameEngineInput::IsDown(VK_LSHIFT, this))
				{
					SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_engage.ogg");
					SlowPlayer.SetVolume(0.3f);
					_Parent->ChangeState(TestLevelState::SlowGame);
					return;
				}

				PressTime = 0.0f;
				GameEngineCore::MainTime.SetGlobalTimeScale(1.0f);

				FreeTime += _Delta / 2;

				if (PlayUIObject != nullptr)
				{
					if (FreeTime > 1.0f)
					{
						if (CurBatteryIndex >= 11)
						{
							CurBatteryIndex = 11;
							return;
						}
						else
						{
							++CurBatteryIndex;

							if (false == PlayUIObject->UIRenderer_BatteryParts[CurBatteryIndex]->GetUpdateValue())
							{
								PlayUIObject->OnBatteryParts(CurBatteryIndex);
							}
						}

						FreeTime = 0.0f;
					}
				}
			};

		NewPara.End = [=](class GameEngineState* _Parent)
			{

			};

		TestLevelState.CreateState(TestLevelState::PlayGame, NewPara);
	}


	// SlowGame
	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				GameEngineCore::MainTime.SetGlobalTimeScale(0.1f);
			};

		NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
			{
				if (CurBatteryIndex < 0)
				{
					TestLevelState.ChangeState(TestLevelState::PlayGame);
					return;
				}

				if (GameEngineInput::IsUp(VK_LSHIFT, this))
				{
					SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_disengage.wav");
					SlowPlayer.SetVolume(1.0f);
					TestLevelState.ChangeState(TestLevelState::PlayGame);
					return;
				}

				GameEngineCore::MainTime.SetGlobalTimeScale(0.1f);
				PressTime += (_Delta * 5.0f);

				// 1�ʿ� �ѹ��� �ε����� �پ���.

				if (PressTime > 1.0f)
				{
					if (CurBatteryIndex >= 0)
					{
						if (true == PlayUIObject->UIRenderer_BatteryParts[CurBatteryIndex]->GetUpdateValue())
						{
							PlayUIObject->OffBatteryParts(CurBatteryIndex);
						}

						// �� ���� ������Ʈ�� ��� ������ �ű��
						--CurBatteryIndex;
					}
					else
					{
						return;
					}

					// Ÿ�̸� �ʱ�ȭ
					PressTime = 0.0f;
				}
			};

		TestLevelState.CreateState(TestLevelState::SlowGame, NewPara);
	}

	TestLevelState.ChangeState(TestLevelState::PlayGame);

}

void MainLevel2_2::Update(float _Delta)
{
	TestLevelState.Update(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("MainLevel2_3");
	}

	// ������Ʈ�� ������ ����
	//static float PressTime = 0.0f;
	//static float FreeTime = 0.0f;
	//static int   CurBatteryIndex = 11;

	// �� PlayLevel�̶�� ���� Ŭ�������� ������ �ִ� �� ���� �� ����.
	// LSHIFTŰ�� ������ ���� ���� ���� �ð� �������� ���͸� ĭ�� 1�� �������,
	// ���� ���� �ݴ�� ���� �ð� �������� ���͸� ĭ�� 1�� �þ��.
	// ���͸� ĭ�� 0�� ���� �ð� ������ ����� �� ����. (�뽬 ����)


	//if (true == GameEngineInput::IsDown(VK_LSHIFT, this))
	//{
	//	SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_engage.ogg");
	//	SlowPlayer.SetVolume(0.3f);
	//}

	//else if (GameEngineInput::IsPress(VK_LSHIFT, this))
	//{
	//	if (CurBatteryIndex < 0)
	//	{
	//		return;
	//	}

	//	GameEngineCore::MainTime.SetGlobalTimeScale(0.1f);
	//	PressTime += (_Delta * 5.0f);

	//	// 1�ʿ� �ѹ��� �ε����� �پ���.

	//	if (PressTime > 1.0f)
	//	{
	//		if (CurBatteryIndex >= 0)
	//		{
	//			if (true == PlayUIObject->UIRenderer_BatteryParts[CurBatteryIndex]->GetUpdateValue())
	//			{
	//				PlayUIObject->OffBatteryParts(CurBatteryIndex);
	//			}

	//			// �� ���� ������Ʈ�� ��� ������ �ű��
	//			--CurBatteryIndex;
	//		}
	//		else
	//		{
	//			return;
	//		}

	//		// Ÿ�̸� �ʱ�ȭ
	//		PressTime = 0.0f;
	//	}
	//}

	// ��ư�� ���� �ִ� ���¿����� ���� �������� �־��� ��ġ ���ĺ��� ��ĭ�� ����ȭ �Ǿ�� �Ѵ�.
	// ��, �ε����� �ʿ��ϴ�.
	// �ٽ� ä�� �� �ε����� �ð��� ������ ���� �ϳ��� �þ�� �Ѵ�.
	// �̶� �ε����� �ִ밪�� 11�� �Ѿ �� ����.

	//else if (GameEngineInput::IsUp(VK_LSHIFT, this))
	//{
	//	SlowPlayer = GameEngineSound::SoundPlay("sound_slomo_disengage.wav");
	//	SlowPlayer.SetVolume(1.0f);
	//}

	//else if (GameEngineInput::IsFree(VK_LSHIFT, this))
	//{
	//	PressTime = 0.0f;
	//	GameEngineCore::MainTime.SetGlobalTimeScale(1.0f);

	//	FreeTime += _Delta / 2;

	//	if (PlayUIObject != nullptr)
	//	{
	//		if (FreeTime > 1.0f)
	//		{
	//			if (CurBatteryIndex >= 11)
	//			{
	//				CurBatteryIndex = 11;
	//				return;
	//			}
	//			else
	//			{
	//				++CurBatteryIndex;

	//				if (false == PlayUIObject->UIRenderer_BatteryParts[CurBatteryIndex]->GetUpdateValue())
	//				{
	//					PlayUIObject->OnBatteryParts(CurBatteryIndex);
	//				}
	//			}

	//			FreeTime = 0.0f;
	//		}
	//	}
	//}

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
	PlayUIObject->UseBattery();
	PlayUIObject->UseItem();
	PlayUIObject->UseTimer();
	PlayUIObject->UseWeapon();
//Player::MainPlayer->IsUseInput = true;
}

void MainLevel2_2::FSM_Intro_Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON, this))
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
