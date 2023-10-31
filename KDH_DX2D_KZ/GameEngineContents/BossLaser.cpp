#include "PreCompile.h"
#include "BossLaser.h"

BossLaser::BossLaser()
{
}

BossLaser::~BossLaser()
{
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

	BossLaserCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyAttack);
	BossLaserCollision->Transform.SetLocalScale({ 40, 50, 1 });

	BossLaserRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossLaserRenderer->AutoSpriteSizeOn();
	BossLaserRenderer->SetSprite("Boss_RifleAttackLine.png");
//	BossLaserRenderer->LeftFlip();
// Boss가 부모인 기준 초기값
// 	BossLaserRenderer->Transform.SetLocalPosition({ -560.0f, 14.0f });
//	BossLaserRenderer->Transform.SetLocalPosition({ -560.0f, 14.0f });
	BossLaserRenderer->CreateAnimation("BossLaser", "Boss_Laser");
	BossLaserRenderer->ChangeAnimation("BossLaser");
}

void BossLaser::Update(float _Delta)
{
}
