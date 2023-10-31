#include "PreCompile.h"
#include "BossBullet.h"

BossBullet::BossBullet()
{
}

BossBullet::~BossBullet()
{
}

void BossBullet::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Boss\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("Boss_ExplosionAreaCircle.png"));
		GameEngineSprite::CreateSingle("Boss_ExplosionAreaCircle.png");

		GameEngineTexture::Load(FilePath.PlusFilePath("spr_boss_grenade.png"));
		GameEngineSprite::CreateSingle("spr_boss_grenade.png");
	}

	BossBulletRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossBulletRenderer->SetSprite("spr_boss_grenade.png");
	BossBulletRenderer->AutoSpriteSizeOn();


	BossBulletAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossBulletAreaRenderer->SetSprite("Boss_ExplosionAreaCircle.png");
	BossBulletAreaRenderer->AutoSpriteSizeOn();
	//	BossLaserRenderer->SetSprite("Boss_RifleAttackLine.png");

}

void BossBullet::Update(float _Delta)
{
}
