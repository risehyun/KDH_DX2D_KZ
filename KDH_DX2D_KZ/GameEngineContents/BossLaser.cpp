#include "PreCompile.h"
#include "BossLaser.h"

BossLaser::BossLaser()
{
}

BossLaser::~BossLaser()
{
}

void BossLaser::InitBossLaserData(BossLaserType _Type, float4 _LaserDir, float4 _LaserInitPos, float4 _LaserEndPos = float4::ZERO)
{
	Type = _Type;
	Dir = _LaserDir;
	LaserFirePos = _LaserInitPos;

	BossLaserCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyAttack);
	BossLaserCollision->SetCollisionType(ColType::AABBBOX2D);

	// �����̼��� ���� ���ְ� �������� ��������� ���� �۵���
	if (Type == BossLaserType::Vertical)
	{
		BossLaserRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, 90.0f });
	}
	
	if (Type == BossLaserType::Rot)
	{
		BossLaserRenderer->ChangeAnimation("BossAttackLine_X2");
	}

	if (Type != BossLaserType::Red)
	{
		BossLaserRenderer->Transform.SetLocalPosition(_LaserInitPos);
	}


	BossLaserCollision->Transform.SetLocalPosition(_LaserInitPos);
	BossLaserCollision->Transform.SetLocalScale({ 1047.0f, 30.0f });

	if (Type == BossLaserType::Red)
	{
		BossLaserRenderer->ChangeAnimation("DashLaser");
	}

	if (Dir == float4::LEFT)
	{
		BossLaserRenderer->LeftFlip();
	}
	else if (Dir == float4::RIGHT)
	{
		BossLaserRenderer->RightFlip();
	}
	else if (Dir == float4::DOWN)
	{
		BossLaserRenderer->DownFlip();
	}

}

void BossLaser::Start()
{
	BossLaserRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossLaserRenderer->AutoSpriteSizeOn();

	BossLaserRenderer->CreateAnimation("BossAttackLine", "Boss_AttackLine", 0.2f, 0, 3, false);
	BossLaserRenderer->CreateAnimation("BossAttackLine_X2", "Boss_AttackLine", 0.03f, 0, 3, false);
	BossLaserRenderer->CreateAnimation("BossLaser", "Boss_Laser");
	BossLaserRenderer->CreateAnimation("DashLaser", "Boss_DashLine");
	BossLaserRenderer->ChangeAnimation("BossAttackLine");
}

// �浹�� ���� �浹�� ����� �Ѵ�
void BossLaser::Update(float _Delta)
{

	if ((BossLaserRenderer->IsCurAnimation("BossAttackLine") 
		|| BossLaserRenderer->IsCurAnimation("BossAttackLine_X2"))
		&& true == BossLaserRenderer->IsCurAnimationEnd())
	{
		BossLaserRenderer->ChangeAnimation("BossLaser");
	}

	if (Type == BossLaserType::Rot)
	{
	
		BossLaserRenderer->SetPivotType(PivotType::Left);

		BossLaserRenderer->Transform.AddLocalRotation({ MoveDir * _Delta * Speed });

		// ��ǥ ������ ������ ���
		if (BossLaserRenderer->Transform.GetLocalRotationEuler().Z > 0.0f)
		{
			MoveDir = { 0.0f, 0.0f, 0.0f };
			Death();
		}

		// ���� �������� ���ݾ� ������ �̵�
		if (BossLaserRenderer->Transform.GetLocalRotationEuler().Z < 180.0f)
		{
			MoveDir = { 0.0f, 0.0f, -1.0f };
		}

	}

	else
	{
		if ((BossLaserRenderer->IsCurAnimation("BossLaser")
			|| BossLaserRenderer->IsCurAnimation("BossAttackLine_X2"))
			&& true == BossLaserRenderer->IsCurAnimationEnd()
			&& GetLiveTime() > 2.0f)
		{
			Death();
		}
	}

	if (Type == BossLaserType::Red && true == BossLaserRenderer->IsCurAnimationEnd())
	{
		Death();
	}



}
