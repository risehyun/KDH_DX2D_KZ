#include "PreCompile.h"
#include "Boss.h"

#include "BossLaser.h"
#include "BossBullet.h"

#include "Player.h"

Boss* Boss::Boss_HeadHunter = nullptr;
Boss::Boss()
{
	Boss_HeadHunter = this;
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
	BossMainRenderer->CreateAnimation("TakeOutRifle", "spr_headhunter_takeoutrifle", 0.02f, 0, 7, false);
	BossMainRenderer->CreateAnimation("Shoot", "spr_headhunter_shoot", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("PutBackGun", "spr_headhunter_putbackgun", 0.1f, 0, 6, false);
	BossMainRenderer->CreateAnimation("Sweep", "spr_headhunter_sweep", 0.123f, 0, 17, false);
	BossMainRenderer->CreateAnimation("TeleportIn", "spr_headhunter_teleport_in", 0.1f, 0, 3, false);

	BossMainRenderer->ChangeAnimation("Idle");

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// FSM 등록
	FSM_Boss_Idle();
	FSM_Boss_GroundRifleAttack();
	FSM_Boss_GroundRifleAttackEnd();
	FSM_Boss_AirRifleAttack();
	FSM_Boss_AirRifleAttackEnd();

	FSM_BossState.ChangeState(FSM_BossState::Idle);
}

void Boss::Update(float _Delta)
{
	FSM_BossState.Update(_Delta);


	//if (GameEngineInput::IsDown('G', this))
	//{

	//	BossMainRenderer->ChangeAnimation("Sweep");
	//	BossMainRenderer->RightFlip();

	//}

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