#include "PreCompile.h"
#include "MainLevel1_1.h"
#include "Player.h"
#include "SkyMap.h"

#include "Enemy.h"

#include "Door.h"
#include "Portal.h"
#include "UITrigger.h"

#include "PinPointLight.h"

#include "Map.h"

#include "UI_Mouse.h"
#include "UI_PlayUI.h"
#include "UI_FadeObject.h"


MainLevel1_1::MainLevel1_1()
{
}

MainLevel1_1::~MainLevel1_1()
{
}

void MainLevel1_1::Start()
{
	if (nullptr == GameEngineSound::FindSound("song_silhouette.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Song\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("song_silhouette.ogg"));
	}

	//UIChangeCollision = CreateActor<GameEngineCollision>(ContentsCollisionType::Interactable);
	//UIChangeCollision->Transform.SetLocalScale({ 30, 30, 1 });
	//UIChangeCollision->Transform.SetLocalPosition({100.0f, 100.0f});
}

void MainLevel1_1::Update(float _Delta)
{
	if (GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainLevel2_1");
	}


	if (GameEngineInput::IsDown(VK_F1))
	{
		if (true == IsDebug)
		{
			OffDebug();
		}
		else
		{
			OnDebug();
		}
		
	}

	if (GetLiveTime() > 2.5f && GetLiveTime() < 2.6f)
	{
		ShakeCamera(_Delta);
	}

	UpdateLevelState(_Delta);
}

void MainLevel1_1::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	CameraInitPos = { HalfWindowScale.X, -HalfWindowScale.Y, -500.0f };

	GetMainCamera()->Transform.SetLocalPosition(CameraInitPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ HalfWindowScale.X, 300, -500.0f });

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X - 400.0f, -HalfWindowScale.Y + 150.0f });
		Object->Off();
	}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_MainLevel1_Origin.png", "Map_MainLevel1.png");
	}
	
	{
		std::shared_ptr<Door> DoorObject = CreateActor<Door>();
		DoorObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4390.0f, -HalfWindowScale.Y - 250.0f });
	}

	{
		std::shared_ptr<Portal> PortalObject = CreateActor<Portal>();
		PortalObject->Transform.SetLocalPosition({ HalfWindowScale.X + 4725.0f, -HalfWindowScale.Y - 250.0f });
		PortalObject->InitPortalData("MainLevel2_1", true);
	}


	{
		CreateActor<SkyMap>();
	}

	{
		std::shared_ptr<UITrigger> UITriggerObject = CreateActor<UITrigger>();
		UITriggerObject->Transform.SetLocalPosition({ HalfWindowScale.X + 1400.0f, -HalfWindowScale.Y - 250.0f });
		UITriggerObject->InitUITriggerData(TriggerType::KeyboardW);
	}


	{
		std::shared_ptr<UITrigger> UITriggerObject = CreateActor<UITrigger>();
		UITriggerObject->Transform.SetLocalPosition({ HalfWindowScale.X + 3800.0f, -HalfWindowScale.Y - 250.0f });
		UITriggerObject->InitUITriggerData(TriggerType::GoArrow);
	}

	//{
	//	std::shared_ptr<PinPointLight> LightObject = CreateActor<PinPointLight>();
	//	LightObject->Transform.SetLocalPosition({ HalfWindowScale.X - 150.0f, -HalfWindowScale.Y + 90.0f });
	//}

	{
		PlayUIObject = CreateActor<UI_PlayUI>();
	}

	{
		std::shared_ptr<UI_FadeObject> FadeObject = CreateActor<UI_FadeObject>();
	}

	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->SetEnemyData(EnemyType::NormalGangster);
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 150.0f, -HalfWindowScale.Y + 90.0f });
		EnemyObject->SetMapTexture("Map_MainLevel1.png");
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllEnemy.push_back(EnemyObject);
	}


	Player::MainPlayer->SetMapTexture("Map_MainLevel1.png");

	BGMPlayer.SetVolume(0.3f);
	BGMPlayer = GameEngineSound::SoundPlay("song_silhouette.ogg", 5);


	ChangeLevelState(ELevelState::Intro);
}

void MainLevel1_1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void MainLevel1_1::ShakeCamera(float _Delta)
{
	GameEngineRandom Random;

	float shakeAmount = 3.0f;
	float shakeTime = 1.0f;

	float timer = 0;
	while (timer <= shakeTime)
	{
		float4 RandomShakePos = CameraInitPos.X + Random.RandomFloat(0, 100);
		GetMainCamera()->Transform.SetLocalPosition({ RandomShakePos.X * shakeTime, CameraInitPos.Y });

		timer += _Delta;
	}
}

void MainLevel1_1::ChangeLevelState(ELevelState _NextLevelState)
{
	LevelState = _NextLevelState;

	switch (LevelState)
	{
	case ELevelState::Intro:
		FSM_Intro_Start();
		break;

	case ELevelState::PlayerSpawn:
		FSM_PlayerSpawn_Start();
		break;

	case ELevelState::TimeControl:
		FSM_TimeControl_Start();
		break;

	case ELevelState::StartGame:
		FSM_StartGame_Start();
		break;

	case ELevelState::Default:
	default:
		break;

	}

}

void MainLevel1_1::UpdateLevelState(float _Delta)
{
	switch (LevelState)
	{
	case ELevelState::Intro:
		FSM_Intro_Update(_Delta);
		break;

	case ELevelState::PlayerSpawn:
		FSM_PlayerSpawn_Update(_Delta);
		break;

	case ELevelState::TimeControl:
		FSM_TimeControl_Update(_Delta);
		break;

	case ELevelState::StartGame:
		FSM_StartGame_Update(_Delta);
		break;

	case ELevelState::Default:
	default:
		break;
	}
}

void MainLevel1_1::FSM_Intro_Start()
{
}

void MainLevel1_1::FSM_PlayerSpawn_Start()
{

}

void MainLevel1_1::FSM_TimeControl_Start()
{
	AllEnemy[0]->ChangeState(EnemyState::Attack);
	PlayUIObject->UIRenderer_LeftClick->On();

	std::shared_ptr<UI_Mouse> CursorObject = CreateActor<UI_Mouse>();
}

void MainLevel1_1::FSM_StartGame_Start()
{
	PlayUIObject->UIRenderer_LeftClick->Off();
	PlayUIObject->Renderer_PressKeyboard->On();
}

void MainLevel1_1::FSM_Intro_Update(float _Delta)
{
	// 글로벌 값으로 추후에 빼기
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	if(GetLiveTime() > 2.7f)
	{
		std::shared_ptr<Enemy> EnemyObject = CreateActor<Enemy>();
		EnemyObject->SetEnemyData(EnemyType::ColoredGangster);
		EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 300.0f, -HalfWindowScale.Y + 300.0f });
		EnemyObject->SetMapTexture("Map_MainLevel1.png");
		EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
		AllEnemy.push_back(EnemyObject);
		AllEnemy[0]->ChangeEmotion(EEnemyState_Emotion::Question);
		ChangeLevelState(ELevelState::PlayerSpawn);
	}
}

void MainLevel1_1::FSM_PlayerSpawn_Update(float _Delta)
{
	float4 MovePos;

	if (GetLiveTime() > 5.0f && GetLiveTime() < 5.1f)
	{
		Player::MainPlayer->On();
		Player::MainPlayer->ChangeState(PlayerState::Fall);
		AllEnemy[0]->ChangeEmotion(EEnemyState_Emotion::HardExclamation);

	}

	if (GetLiveTime() > 6.5f && GetLiveTime() < 6.6f)
	{
		AllEnemy[0]->ChangeState(EnemyState::Turn);
	}

	if (GetLiveTime() > 7.0f 
		&& Player::MainPlayer->GetMainRenderer()->IsCurAnimation("Idle")
		&& Player::MainPlayer->GetMainRenderer()->IsCurAnimationEnd())
	{
		Player::MainPlayer->ChangeState(PlayerState::Roll);


		if (GetLiveTime() < 10.0f)
		{
			MovePos = { float4::RIGHT * _Delta * 200.0f };

			while (Player::MainPlayer->Transform.GetLocalPosition().X < 700.0f)
			{
				Player::MainPlayer->Transform.AddLocalPosition(MovePos);

				AllEnemy[0]->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);

				if (Player::MainPlayer->GetMainRenderer()->IsCurAnimationEnd())
				{
					Player::MainPlayer->ChangeState(PlayerState::Run);
				}
			}

			Player::MainPlayer->GetMainRenderer()->LeftFlip();
			AllEnemy[0]->ChangeState(EnemyState::Idle);

			ChangeLevelState(ELevelState::TimeControl);

		}
	}

}

void MainLevel1_1::FSM_TimeControl_Update(float _Delta)
{
	if(Player::MainPlayer->GetMainRenderer()->IsCurAnimation("Attack"))
	{
		ChangeLevelState(ELevelState::StartGame);
	}
}

void MainLevel1_1::FSM_StartGame_Update(float _Delta)
{
	PlayUIObject->PlayUI->Renderer_PressKeyboard->Transform.SetLocalPosition
	({Player::MainPlayer->Transform.GetLocalPosition().X, 
		Player::MainPlayer->Transform.GetLocalPosition().Y + 100.0f});
}
