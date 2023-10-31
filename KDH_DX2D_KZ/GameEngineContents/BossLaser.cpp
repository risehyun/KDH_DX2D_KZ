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

	BossLaserRenderer->CreateAnimation("BossLaser", "Boss_Laser");
	BossLaserRenderer->ChangeAnimation("BossLaser");


}

// �浹�� ���� �浹�� ����� �Ѵ�
void BossLaser::Update(float _Delta)
{
	if (Type == BossLaserType::Rot)
	{
		BossLaserRenderer->SetPivotType(PivotType::Left);

		BossLaserRenderer->Transform.AddLocalRotation({ MoveDir * _Delta * Speed });

		// ��ǥ ���� ����
		if (BossLaserRenderer->Transform.GetLocalRotationEuler().Z <= -170.0f)
		{
			MoveDir = { 0.0f, 0.0f, 0.0f };
			Death();
		}

		// ���� �������� ���ݾ� ������ �̵�
		if (BossLaserRenderer->Transform.GetLocalRotationEuler().Z >= -1.0f)
		{
			MoveDir = { 0.0f, 0.0f, -1.0f };
		}




	}

}
