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

MainLevel2_3::MainLevel2_3()
{
}

MainLevel2_3::~MainLevel2_3()
{
}

void MainLevel2_3::ChangeLevelState(ELevelState _NextLevelState)
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

void MainLevel2_3::UpdateLevelState(float _Delta)
{

}

void MainLevel2_3::FSM_Intro_Start()
{
}

void MainLevel2_3::FSM_StartGame_Start()
{
}

void MainLevel2_3::Start()
{
	GameEngineInput::AddInputObject(this);
}

void MainLevel2_3::Update(float _Delta)
{
	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("MainLevel2_4");
	}
}

void MainLevel2_3::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ HalfWindowScale.X, 300, -500.0f });

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

	{
		std::shared_ptr<UI_PlayUI> UIObject = CreateActor<UI_PlayUI>();
		UIObject->UseHUD();
		UIObject->UseBattery();
		UIObject->UseItem();
		UIObject->UseTimer();
		UIObject->UseWeapon();
	}

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
}

void MainLevel2_3::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}
