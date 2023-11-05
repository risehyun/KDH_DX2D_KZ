#include "PreCompile.h"
#include "Boss.h"
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
	BossMainRenderer->CreateAnimation("TakeOutGun", "spr_headhunter_takeoutgun", 0.1f, 0, 6, false);

	BossMainRenderer->CreateAnimation("TeleportOut", "spr_headhunter_teleport_out", 0.1f, 0, 3, false);
	BossMainRenderer->CreateAnimation("TeleportIn", "spr_headhunter_teleport_in", 0.1f, 0, 3, false);

	BossMainRenderer->CreateAnimation("Sweep", "spr_headhunter_sweep", 0.123f, 0, 17, false);
	BossMainRenderer->CreateAnimation("SweepTeleportOut", "spr_headhunter_teleport_out_sweep", 0.1f, 0, 2, false);
	BossMainRenderer->CreateAnimation("SweepTeleportIn", "spr_headhunter_teleport_in_sweep", 0.1f, 0, 3, false);

	BossMainRenderer->CreateAnimation("PreDash", "spr_headhunter_predash", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("Dash", "spr_headhunter_dash");
	BossMainRenderer->CreateAnimation("DashEnd", "spr_headhunter_dash_end_ground", 0.1f, 0, 9, false);

	BossMainRenderer->CreateAnimation("WallIdle", "spr_headhunter_wall_idle", 0.1f, 0, 2, false);
	BossMainRenderer->CreateAnimation("WallJump", "spr_headhunter_walljump", 0.25f, 0, 6, false);
	BossMainRenderer->CreateAnimation("WallLand", "spr_headhunter_walljump_land", 0.1f, 0, 3, false);
	




	BossMainRenderer->ChangeAnimation("Idle");

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// FSM µî·Ï
	FSM_Boss_Idle();

	FSM_Boss_GroundRifleAttack();
	FSM_Boss_GroundRifleAttackEnd();

	FSM_Boss_AirRifleAttack_Start();
	FSM_Boss_AirRifleAttack();
	FSM_Boss_AirRifleAttackEnd();

	FSM_Boss_MultipleAirRifleAttack();

	FSM_Boss_GroundDashAttack();
	FSM_Boss_AirDashAttack();

	FSM_Boss_WallJump_Start();
	FSM_Boss_WallJump();
	FSM_Boss_WallJump_End();

	FSM_Boss_GrenadeAttack_Start();
	FSM_Boss_GrenadeAttack();
	FSM_Boss_GrenadeAttack_End();

	FSM_Boss_WallTurretAttack();


	SetCharacterType(CharacterType::Boss);
	FSM_BossState.ChangeState(FSM_BossState::Idle);
}

void Boss::Update(float _Delta)
{
	FSM_BossState.Update(_Delta);
}