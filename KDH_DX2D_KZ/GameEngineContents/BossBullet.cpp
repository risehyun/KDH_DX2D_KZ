#include "PreCompile.h"
#include "BossBullet.h"
#include "FX_Explosion.h"

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

		//GameEngineTexture::Load(FilePath.PlusFilePath("Boss_ExplosionAreaCircle.png"));
		//GameEngineSprite::CreateSingle("Boss_ExplosionAreaCircle.png");

		GameEngineTexture::Load(FilePath.PlusFilePath("spr_boss_grenade.png"));
		GameEngineSprite::CreateSingle("spr_boss_grenade.png");
	}

	BossBulletRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossBulletRenderer->SetSprite("spr_boss_grenade.png");
	BossBulletRenderer->AutoSpriteSizeOn();


	BossBulletAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossBulletAreaRenderer->CreateAnimation("ExplosionCircle", "Boss_ExplosionArea");
	BossBulletAreaRenderer->ChangeAnimation("ExplosionCircle");
		//SetSprite("Boss_ExplosionAreaCircle.png");
	BossBulletAreaRenderer->AutoSpriteSizeOn();
	BossBulletAreaRenderer->Off();
	//	BossLaserRenderer->SetSprite("Boss_RifleAttackLine.png");

}

void BossBullet::Update(float _Delta)
{
	if (GetLiveTime() > 2.0f)
	{
		BossBulletAreaRenderer->On();
	}

	if (BossBulletAreaRenderer->IsCurAnimationEnd())
	{		
		BossBulletAreaRenderer->Off();
	}

	if (GetLiveTime() > 3.0f && GetLiveTime() < 3.1f)
	{
		GameEngineRandom Random;

		// 이동 위치 랜덤 설정

		for (int i = 0; i < 50; i++)
		{
			int RandomPosX = Random.RandomInt(-110, 110);
			int RandomPosY = Random.RandomInt(-130, 130);

			std::shared_ptr<FX_Explosion> EnemyNewBullet = GetLevel()->CreateActor<FX_Explosion>(static_cast<int>(ContentsRenderType::Play));
			EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + RandomPosX, Transform.GetLocalPosition().Y + RandomPosY });
		}
	}


	if (GetLiveTime() > 3.5f)
	{
		Death();
	}


}