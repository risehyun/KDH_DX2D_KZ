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

	BossBulletRenderer->Transform.SetLocalRotation({0.0f, 0.0f, 90.0f});

	BossBulletRenderer->SetSprite("Boss_Bullet.bmp");
}

void BossBullet::Update(float _Delta)
{
//	Transform.AddLocalRotation({ 0.0, 0.0f, MovePos.X });
//	Transform.AddLocalPosition(MovePos * _Delta * 300.0f);

	Transform.AddLocalPosition({ arrowPower * MovePos.X, arrowPower * MovePos.Y });


	//if (float4::LEFT == Boss::Boss_HeadHunter->GetBossDir())
	//{
	//	Transform.AddLocalPosition(float4::LEFT * _Delta * 200.0f);
	//}

	//if (float4::RIGHT == Boss::Boss_HeadHunter->GetBossDir())
	//{
	//	Transform.AddLocalPosition(float4::RIGHT * _Delta * 200.0f);
	//}

	if (GetLiveTime() > 2.0f)
	{
		Death();
	}
}