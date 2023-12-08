#include "PreCompile.h"
#include "BossBullet.h"
#include "FX_Explosion.h"
#include "Boss.h"

BossBullet::BossBullet()
{
}

BossBullet::~BossBullet()
{
}

void BossBullet::Start()
{
	BossBulletRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Boss\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("Boss_Bullet.bmp"));
		GameEngineSprite::CreateSingle("Boss_Bullet.bmp");
	}


	BossBulletRenderer->AutoSpriteSizeOn();

	BossBulletRenderer->Transform.SetLocalRotation({0.0f, 0.0f, -90.0f});

	BossBulletRenderer->SetSprite("Boss_Bullet.bmp");

	BossBulletCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyAttack);
	BossBulletCollision->SetCollisionType(ColType::SPHERE2D);
	BossBulletCollision->Transform.SetLocalScale({ 40.0f, 40.0f });
}

void BossBullet::SetDirection(const float4& _Direction)
{
	MoveDir = _Direction;
}

void BossBullet::Update(float _Delta)
{
//	Transform.AddLocalRotation({ 0.0, 0.0f, MovePos.X });

	const float4 MoveVector = MoveDir * BulletPower* _Delta;
	Transform.AddLocalPosition(MoveVector);

	if (GetLiveTime() > 2.0f)
	{
		Death();
	}
}