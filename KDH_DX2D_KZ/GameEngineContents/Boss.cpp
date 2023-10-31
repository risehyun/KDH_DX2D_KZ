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

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Boss\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("Boss_ExplosionAreaCircle.png"));
		GameEngineSprite::CreateSingle("Boss_ExplosionAreaCircle.png");


		//GameEngineTexture::Load(FilePath.PlusFilePath("Boss_RifleAttackLine.png"));
		//GameEngineSprite::CreateSingle("Boss_RifleAttackLine.png");

	}

	BossMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossMainRenderer->AutoSpriteSizeOn();

	BossMainRenderer->CreateAnimation("Idle", "spr_headhunter_idle");
	BossMainRenderer->CreateAnimation("PutBackRifle", "spr_headhunter_putbackrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("TakeOutRifle", "spr_headhunter_takeoutrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("Shoot", "spr_headhunter_shoot", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("PutBackGun", "spr_headhunter_putbackgun", 0.1f, 0, 6, false);

	BossMainRenderer->ChangeAnimation("TakeOutRifle");

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();


	//	EnemyNewBullet->Transform.SetLocalPosition({ -560.0f, 14.0f });

	//	EnemyNewBullet->Transform.SetLocalPosition({ -560.0f, 14.0f });
	//	EnemyNewBullet
	//	BossMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);
	//	BossMainRenderer->CreateAnimation("Turn", "spr_gangsterturn", 0.2f, 0, 5, false);

		//BossEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		//BossEffectRenderer->AutoSpriteSizeOn();
		//BossEffectRenderer->LeftFlip();
		//BossEffectRenderer->Transform.SetLocalPosition({ -560.0f, 14.0f });
		//BossEffectRenderer->CreateAnimation("BossLaser", "Boss_Laser");
		//BossEffectRenderer->ChangeAnimation("BossLaser");
		//BossEffectRenderer->Off();
}

void Boss::Update(float _Delta)
{
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
		std::shared_ptr<BossLaser> EnemyNewBullet = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		EnemyNewBullet->InitBossLaserData(BossLaserType::Rot, float4::DOWN, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y + 200.0f });
	}

	if (GameEngineInput::IsDown('H', this))
	{
		DirCheck();

		std::shared_ptr<BossBullet> EnemyNewBullet = GetLevel()->CreateActor<BossBullet>(static_cast<int>(ContentsRenderType::Play));
		
		if (Dir == BossDir::Left)
		{
			EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X - 200.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
		else
		{
			EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + 200.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
	}
	



}