#include "PreCompile.h"
#include "WallOpen.h"
#include "Enemy.h"

WallOpen::WallOpen()
{
}

WallOpen::~WallOpen()
{
}

void WallOpen::Start()
{
	WallOpenRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));
	WallOpenRenderer->AutoSpriteSizeOn();
	WallOpenRenderer->CreateAnimation("WallOpen", "spr_bunker_turret_wall_open", 0.1f, 0, 20, false);
	WallOpenRenderer->ChangeAnimation("WallOpen");
}

void WallOpen::Update(float _Delta)
{
	if (WallOpenRenderer->IsCurAnimationEnd() && false == IsCreateTurret)
	{
		float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

		{
			std::shared_ptr<Enemy> EnemyObject = GetLevel()->CreateActor<Enemy>();
			EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 426.0f, -HalfWindowScale.Y - 70.0f });
			EnemyObject->SetMapTexture("Map_BossLevel1_2.png");
			EnemyObject->SetEnemyData(EnemyType::WallTurret, EnemyDir::Right);
			EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
			EnemyObject->FSM_EnemyState.ChangeState(FSM_EnemyState::Appear);
		}

		{
			std::shared_ptr<Enemy> EnemyObject = GetLevel()->CreateActor<Enemy>();
			EnemyObject->Transform.SetLocalPosition({ HalfWindowScale.X - 426.0f, -HalfWindowScale.Y + 30.0f });
			EnemyObject->SetMapTexture("Map_BossLevel1_2.png");
			EnemyObject->SetEnemyData(EnemyType::WallTurret, EnemyDir::Right);
			EnemyObject->ChangeEmotion(EEnemyState_Emotion::Default);
			EnemyObject->FSM_EnemyState.ChangeState(FSM_EnemyState::Appear);
		}

		IsCreateTurret = true;
	}
}
