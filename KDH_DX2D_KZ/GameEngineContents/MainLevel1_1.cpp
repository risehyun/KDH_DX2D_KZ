#include "PreCompile.h"
#include "MainLevel1_1.h"
#include "Player.h"
#include "SkyMap.h"

#include "Enemy.h"
#include "Door.h"
#include "Portal.h"

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

	//{
	//	std::shared_ptr<PinPointLight> LightObject = CreateActor<PinPointLight>();
	//	LightObject->Transform.SetLocalPosition({ HalfWindowScale.X - 150.0f, -HalfWindowScale.Y + 90.0f });
	//}





	{
		std::shared_ptr<UI_Mouse> CursorObject = CreateActor<UI_Mouse>();
	}

	
	{
		std::shared_ptr<UI_PlayUI> PlayUIObject = CreateActor<UI_PlayUI>();
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

//	GetMainCamera()->Transform.SetLocalPosition(CameraInitPos);
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
}

void MainLevel1_1::FSM_StartGame_Start()
{
}

void MainLevel1_1::FSM_Intro_Update(float _Delta)
{
	// �۷ι� ������ ���Ŀ� ����
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
	}

	if (GetLiveTime() > 7.0f && Player::MainPlayer->GetMainRenderer()->IsCurAnimationEnd())
	{
		Player::MainPlayer->ChangeState(PlayerState::Roll);

		if (GetLiveTime() < 10.0f)
		{
			MovePos = { float4::RIGHT * _Delta * 200.0f };
			Player::MainPlayer->Transform.AddLocalPosition(MovePos);
			if (Player::MainPlayer->GetMainRenderer()->IsCurAnimationEnd())
			{
				Player::MainPlayer->ChangeState(PlayerState::Run);
			}
		}
	}



	

	



}

void MainLevel1_1::FSM_TimeControl_Update(float _Delta)
{
}

void MainLevel1_1::FSM_StartGame_Update(float _Delta)
{
}
