#include "PreCompile.h"
#include "BossGrenade.h"
#include "FX_Explosion.h"

BossGrenade::BossGrenade()
{
}

BossGrenade::~BossGrenade()
{
}

void BossGrenade::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Boss\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("spr_boss_grenade.png"));
		GameEngineSprite::CreateSingle("spr_boss_grenade.png");
	}

	BossBulletRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossBulletRenderer->SetSprite("spr_boss_grenade.png");
	BossBulletRenderer->AutoSpriteSizeOn();

	BossBulletAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossBulletAreaRenderer->CreateAnimation("ExplosionCircle", "Boss_ExplosionArea", 0.1f, 0, 11, false);
	BossBulletAreaRenderer->ChangeAnimation("ExplosionCircle");
	BossBulletAreaRenderer->AutoSpriteSizeOn();
	BossBulletAreaRenderer->Off();

	SetMapTexture("Map_BossLevel1_2.png");
}

void BossGrenade::Update(float _Delta)
{
	if (GetLiveTime() < 2.0f)
	{

		GameEngineRandom Random;

		// 이동 위치 랜덤 설정
		int Count = Random.RandomInt(0, 2);
		switch (Count)
		{
		case 0:

			break;

		case 1:

			break;

		case 2:

			break;

		default:
			break;
		}



		if (false == IsOnCurve)
		{
			float4 CheckPos = { Transform.GetWorldPosition() + UpCheck };

			GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

			if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
			{
				MovePos = { (float4::LEFT + float4::UP) * 300.0f * _Delta };
			}
			else
			{
				IsOnCurve = true;
			}

		}

		if (true == IsOnCurve)
		{

			float4 CheckPos = { Transform.GetWorldPosition() + LeftCheck + DownCheck };

			GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

			if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
			{
				MovePos = { (float4::LEFT + float4::DOWN) * 300.0f * _Delta };
			}
			else
			{

			}

		}

		Transform.AddLocalPosition(MovePos);

		//		Transform.AddLocalPosition({ -1.0f * _Delta * 200.0f, 1.0f * _Delta * 200.0f });
	}


	if (GetLiveTime() > 2.0f)
	{
		BossBulletAreaRenderer->On();
	}

	if (BossBulletAreaRenderer->IsCurAnimationEnd())
	{
		BossBulletAreaRenderer->Off();
	}

	if (GetLiveTime() > 3.7f && GetLiveTime() < 3.8f)
	{
		BossBulletRenderer->Off();
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

	if (GetLiveTime() > 4.0f)
	{
		Death();
	}
}