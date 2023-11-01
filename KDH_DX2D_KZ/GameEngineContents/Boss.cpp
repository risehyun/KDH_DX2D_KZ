#include "PreCompile.h"
#include "Boss.h"

#include "BossLaser.h"
#include "BossBullet.h"

#include "Player.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::DirCheck()
{
	float4 DirDeg = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

	if (DirDeg.Angle2DDeg() > 90.0f && DirDeg.Angle2DDeg() < 270.0f)
	{
		Dir = BossDir::Left;
		BossMainRenderer->LeftFlip();
		//		BossEffectRenderer->LeftFlip();
		return;
	}
	else
	{
		Dir = BossDir::Right;
		BossMainRenderer->RightFlip();
		//		BossEffectRenderer->RightFlip();
		return;
	}
}

void Boss::Start()
{
	GameEngineInput::AddInputObject(this);

	BossMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossMainRenderer->AutoSpriteSizeOn();

	BossMainRenderer->CreateAnimation("Idle", "spr_headhunter_idle");
	BossMainRenderer->CreateAnimation("PutBackRifle", "spr_headhunter_putbackrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("TakeOutRifle", "spr_headhunter_takeoutrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("Shoot", "spr_headhunter_shoot", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("PutBackGun", "spr_headhunter_putbackgun", 0.1f, 0, 6, false);
	BossMainRenderer->CreateAnimation("Sweep", "spr_headhunter_sweep", 0.123f, 0, 17, false);
	BossMainRenderer->CreateAnimation("TeleportIn", "spr_headhunter_teleport_in", 0.1f, 0, 3, false);

	BossMainRenderer->ChangeAnimation("Idle");

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// FSM 등록
	FSM_Boss_Idle();
	FSM_Boss_GroundRifleAttack();

	FSM_BossState.ChangeState(FSM_BossState::GroundRifleAttack);
}

void Boss::Update(float _Delta)
{
	FSM_BossState.Update(_Delta);



	if (GameEngineInput::IsDown('F', this))
	{
		DirCheck();

		std::shared_ptr<BossLaser> EnemyNewBullet = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		if (Dir == BossDir::Left)
		{
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::LEFT, { Transform.GetLocalPosition().X - 550.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
		else
		{
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::RIGHT, { Transform.GetLocalPosition().X + 550.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
	}

	if (GameEngineInput::IsDown('G', this))
	{

		BossMainRenderer->ChangeAnimation("Sweep");
		BossMainRenderer->RightFlip();

		GameEngineRandom Random;

		// 이동 위치 랜덤 설정
		int Count = Random.RandomInt(0, 2);
		switch (Count)
		{
			// 중앙
		case 0:
			Transform.SetLocalPosition({ 550, -250 });
			break;

			// 왼쪽
		case 1:
			Transform.SetLocalPosition({ 250, -250 });
			break;

			// 오른쪽
		case 2:
			Transform.SetLocalPosition({ 1000, -250 });
			break;

		default:
			break;
		}

		std::shared_ptr<BossLaser> EnemyNewBullet = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		EnemyNewBullet->InitBossLaserData(BossLaserType::Rot, float4::DOWN, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f });
	}

	if (GameEngineInput::IsDown('H', this))
	{
		DirCheck();

		std::shared_ptr<BossBullet> EnemyNewBullet = GetLevel()->CreateActor<BossBullet>(static_cast<int>(ContentsRenderType::Play));
		
		if (Dir == BossDir::Left)
		{
			EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X - 40.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
		else
		{
			EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + 200.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
	}

	// 스테이트 적용 해야 정상 작동
	if (GameEngineInput::IsDown('J', this))
	{
		
			Transform.SetLocalPosition({ 250, -250 });
			BossMainRenderer->ChangeAnimation("TeleportIn");
			
			if (GameEngineInput::IsDown('1', this))
			Transform.SetLocalPosition({ 1000, -250 });
		
			if (GameEngineInput::IsDown('2', this))
			Transform.SetLocalPosition({ 450, -250 });

			if (GameEngineInput::IsDown('3', this))
			Transform.SetLocalPosition({ 850, -250 });

	}
	



}