#include "PreCompile.h"
#include "MainLevel2_4.h"
#include "Player.h"

#include "Laser.h"
#include "LaserGroup.h"

#include "Door.h"

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
}

void MainLevel2_4::Update(float _Delta)
{

	CameraFocus(_Delta);

	if (GameEngineInput::IsDown('P', this))
	{
		GameEngineCore::ChangeLevel("MainLevel2_5");
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
		std::shared_ptr<Player> Object = CreateActor<Player>();
		// 1�� ���� ����
		// Object->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y - 480.0f });
		// 2�� Object->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y });
		// 3��
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 600.0f, -HalfWindowScale.Y + 200.0f });

		Object->GetMainRenderer()->LeftFlip();
	}


	// 1�� ������-> x�� ���� 60�� ����
	{
		std::shared_ptr<LaserGroup> Object = CreateActor<LaserGroup>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 43.0f, -HalfWindowScale.Y - 438.0f });
		Object->InitLaserGroupData(6, { HalfWindowScale.X + 43.0f, -HalfWindowScale.Y - 438.0f }, 60.0f, false, false);
	}

	// 2�� ������ -> x�� ���� 196�� ����
	{
		std::shared_ptr<LaserGroup> Object = CreateActor<LaserGroup>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 382.0f, -HalfWindowScale.Y - 80.0f });
		Object->InitLaserGroupData(2, { HalfWindowScale.X + 382.0f, -HalfWindowScale.Y - 80.0f }, 196.0f, true, false);
	}

	// 3�� ������ -> x�� ���� 62�� ����
	{
		std::shared_ptr<LaserGroup> Object = CreateActor<LaserGroup>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X + 144.0f, -HalfWindowScale.Y + 170.0f });
		Object->InitLaserGroupData(3, { HalfWindowScale.X + 10.0f, -HalfWindowScale.Y + 170.0f }, 62.0f, false, true);
	}

	// 3�� ��
	{
		// �� �� �ʱ� ������ �ٲ� �� �־�� ��. �ʱ� ���� �������� �浹ü�� ��ġ �����ϵ��� ����
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


	Player::MainPlayer->SetMapTexture("Map_MainLevel2_4.png");

	BGMPlayer = GameEngineSound::SoundPlay("song_silhouette.ogg", 5);
	BGMPlayer.SetVolume(0.5f);
}

void MainLevel2_4::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}
