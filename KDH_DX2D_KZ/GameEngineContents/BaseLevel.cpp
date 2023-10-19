#include "PreCompile.h"
#include "BaseLevel.h"
#include "Player.h"
#include "GameStateManager.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::Start()
{
	// ������ Input ������ ���·� ����
	GameEngineInput::AddInputObject(this);

#pragma region Level FSM ���

	// �� �������� ���� FSM�� �ְ� �ƴѰ� �ֱ� ������... �̰͵� ����ؼ� �����ؾ� �� �� ����.
	FSM_Level_PlayGame();
	FSM_Level_SlowGame();

	LevelState.ChangeState(LevelState::PlayGame);

#pragma endregion

#pragma region ���� ȿ���� �ε�
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
#pragma endregion

}

void BaseLevel::Update(float _Delta)
{
	// Level FSM �۵�
	LevelState.Update(_Delta);

}

void BaseLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
//	InitCameraSetting();

	{
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}
}

void BaseLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void BaseLevel::InitCameraSetting()
{
//	1280 * 720

//	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	CameraInitPos = { 640.0f, -360.0f, -500.0f };

	GetMainCamera()->Transform.SetLocalPosition(CameraInitPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ 640.0f, 300.0f, -500.0f });
}

void BaseLevel::FSM_Level_PlayGame()
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

			if (PlayUIObject != nullptr)
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

						PlayUIObject->OnBatteryParts(GameStateManager::GameState->CurTimeControlBattery);

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

void BaseLevel::FSM_Level_SlowGame()
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

			// 1�ʿ� �ѹ��� �ε����� �پ���.

			if (PressTimeControlTime > 1.0f)
			{
				if (GameStateManager::GameState->CurTimeControlBattery >= 0)
				{
					if (true == PlayUIObject->UIRenderer_BatteryParts[GameStateManager::GameState->CurTimeControlBattery]->GetUpdateValue())
					{
						PlayUIObject->OffBatteryParts(GameStateManager::GameState->CurTimeControlBattery);
					}

					// �� ���� ������Ʈ�� ��� ������ �ű��
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
