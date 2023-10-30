#include "PreCompile.h"
#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::DirCheck()
{
}

void Boss::Start()
{

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Boss\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("Boss_ExplosionAreaCircle.png"));
		GameEngineSprite::CreateSingle("Boss_ExplosionAreaCircle.png");


		GameEngineTexture::Load(FilePath.PlusFilePath("Boss_RifleAttackLine.png"));
		GameEngineSprite::CreateSingle("Boss_RifleAttackLine.png");

	}



	BossMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossMainRenderer->AutoSpriteSizeOn();

	BossMainRenderer->CreateAnimation("Idle", "spr_headhunter_idle");
	BossMainRenderer->CreateAnimation("PutBackRifle", "spr_headhunter_putbackrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("TakeOutRifle", "spr_headhunter_takeoutrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("Shoot", "spr_headhunter_shoot", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("PutBackGun", "spr_headhunter_putbackgun", 0.1f, 0, 6, false);
	
	BossMainRenderer->ChangeAnimation("PutBackGun");
	
//	BossMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);
//	BossMainRenderer->CreateAnimation("Turn", "spr_gangsterturn", 0.2f, 0, 5, false);

	




	BossEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossEffectRenderer->AutoSpriteSizeOn();
	BossEffectRenderer->LeftFlip();
	BossEffectRenderer->Transform.SetLocalPosition({ -560.0f, 14.0f });
	BossEffectRenderer->CreateAnimation("BossLaser", "Boss_Laser");
	BossEffectRenderer->ChangeAnimation("BossLaser");
	BossEffectRenderer->Off();
}

void Boss::Update(float _Delta)
{
}
