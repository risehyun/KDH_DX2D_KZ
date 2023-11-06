#include "PreCompile.h"
#include "BossLevel1_1.h"
#include "GameStateManager.h"
#include "Player.h"

BossLevel1_1::BossLevel1_1()
{
}

BossLevel1_1::~BossLevel1_1()
{
}

void BossLevel1_1::Start()
{
	GameEngineInput::AddInputObject(this);

	BaseLevel::InitCameraSetting();
}

void BossLevel1_1::Update(float _Delta)
{
}

void BossLevel1_1::LevelStart(GameEngineLevel* _PrevLevel)
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	{
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}

	{
		MapObject = CreateActor<Map>();
		MapObject->InitDebuggedMap("Map_BossLevel1_1_Origin.png", "Map_BossLevel1_1.png");
	}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		// 시작 지점
		Object->Transform.SetLocalPosition({ HalfWindowScale.X - 280.0f, -HalfWindowScale.Y - 150.0f });

		Object->GetMainRenderer()->RightFlip();
		Object->SetMapTexture("Map_BossLevel1_1.png");
	}
}

void BossLevel1_1::LevelEnd(GameEngineLevel* _NextLevel)
{
}
