#include "PreCompile.h"
#include "BossLaser.h"

BossLaser::BossLaser()
{
}

BossLaser::~BossLaser()
{
}

void BossLaser::InitBossLaserData(BossLaserType _Type, float4 _LaserDir, float4 _LaserInitPos)
{
	Type = _Type;
	Dir = _LaserDir;
	LaserFirePos = _LaserInitPos;

	BossLaserCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyAttack);
	BossLaserCollision->SetCollisionType(ColType::AABBBOX2D);

	BossLaserRenderer->Transform.SetLocalPosition(_LaserInitPos);
	BossLaserCollision->Transform.SetLocalPosition(_LaserInitPos);
	BossLaserCollision->Transform.SetLocalScale({ 1047.0f, 30.0f });

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

	if (Type == BossLaserType::Rot)
	{
		BossLaserRenderer->ChangeAnimation("BossAttackLine_X2");
	}



}

void BossLaser::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Boss\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("Boss_RifleAttackLine.png"));
		GameEngineSprite::CreateSingle("Boss_RifleAttackLine.png");
	}

	BossLaserRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossLaserRenderer->AutoSpriteSizeOn();
//	BossLaserRenderer->SetSprite("Boss_RifleAttackLine.png");

	BossLaserRenderer->CreateAnimation("BossAttackLine", "Boss_AttackLine", 0.2f, 0, 3, false);
	BossLaserRenderer->CreateAnimation("BossAttackLine_X2", "Boss_AttackLine", 0.03f, 0, 3, false);
	BossLaserRenderer->CreateAnimation("BossLaser", "Boss_Laser");
	BossLaserRenderer->ChangeAnimation("BossAttackLine");
}

// 충돌은 라인 충돌로 해줘야 한다
void BossLaser::Update(float _Delta)
{

	if (BossLaserRenderer->IsCurAnimation("BossAttackLine") 
		|| BossLaserRenderer->IsCurAnimation("BossAttackLine_X2")
		&& true == BossLaserRenderer->IsCurAnimationEnd())
	{
		BossLaserRenderer->ChangeAnimation("BossLaser");
	}

	if (Type == BossLaserType::Rot)
	{
	
		BossLaserRenderer->SetPivotType(PivotType::Left);

		BossLaserRenderer->Transform.AddLocalRotation({ MoveDir * _Delta * Speed });

		// 목표 지점에 도착한 경우
		if (BossLaserRenderer->Transform.GetLocalRotationEuler().Z > 0.0f)
		{
			MoveDir = { 0.0f, 0.0f, 0.0f };
			Death();
		}

		// 시작 지점부터 조금씩 각도를 이동
		if (BossLaserRenderer->Transform.GetLocalRotationEuler().Z < 180.0f)
		{
			MoveDir = { 0.0f, 0.0f, -1.0f };
		}

	}

	else
	{
		if (BossLaserRenderer->IsCurAnimation("BossLaser")
			|| BossLaserRenderer->IsCurAnimation("BossAttackLine_X2")
			&& true == BossLaserRenderer->IsCurAnimationEnd()
			&& GetLiveTime() > 2.0f)
		{
			Death();
		}
	}

}
