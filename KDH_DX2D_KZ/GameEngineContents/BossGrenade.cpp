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

	BossGrenadeRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossGrenadeRenderer->SetSprite("spr_boss_grenade.png");
	BossGrenadeRenderer->AutoSpriteSizeOn();

	BossGrenadeAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossGrenadeAreaRenderer->CreateAnimation("ExplosionCircle", "Boss_ExplosionArea", 0.1f, 0, 11, false);
	BossGrenadeAreaRenderer->ChangeAnimation("ExplosionCircle");
	BossGrenadeAreaRenderer->AutoSpriteSizeOn();
	BossGrenadeAreaRenderer->Off();

	SetMapTexture("Map_BossLevel1_2.png");

	BossGrenadeCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::BossGrenade);
	BossGrenadeCollision->SetCollisionType(ColType::SPHERE2D);
	BossGrenadeCollision->Transform.SetLocalScale({ 40.0f, 40.0f });

	BossGrenadeAreaCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::BossGrenadeArea);
	BossGrenadeAreaCollision->SetCollisionType(ColType::SPHERE2D);
	BossGrenadeAreaCollision->Transform.SetLocalScale({ 270.0f, 270.0f });
	BossGrenadeAreaCollision->Off();

}

void BossGrenade::Update(float _Delta)
{
	static const float4 gravity = { 0.0f, -9.8f };
	static const float coef_res = 0.5f;

	if (GetLiveTime() < 2.0f)
	{
		vel += gravity * _Delta * Speed;
		Transform.AddLocalPosition(vel * _Delta);

		OutputDebugStringA(std::to_string(Transform.GetLocalPosition().Y + '\n').c_str());

		Transform.AddLocalPosition(MovePos * 300.0f * _Delta);

		// 아래
		if (-535.0f > Transform.GetLocalPosition().Y)
		{
			MovePos = { (float4::UP) * coef_res };
			vel = 0.0f;
		}

		else
		{
			// 위
			if (-204.0f < Transform.GetLocalPosition().Y)
			{
				MovePos = { (float4::LEFT + float4::DOWN) * coef_res };
			}

			// 오른쪽
			else if (1128.0f < Transform.GetLocalPosition().X)
			{
				MovePos = { (float4::LEFT + float4::DOWN) * coef_res };
			}

			// 왼쪽
			else if (160.0f > Transform.GetLocalPosition().X)
			{
				MovePos = { (float4::RIGHT + float4::DOWN) * coef_res };
			}
		}
	}

	if (GetLiveTime() > 2.0f)
	{
		BossGrenadeCollision->Off();
		BossGrenadeAreaRenderer->On();
	}

	if (BossGrenadeAreaRenderer->IsCurAnimationEnd())
	{
		BossGrenadeAreaRenderer->Off();
	}

	if (GetLiveTime() > 3.7f && GetLiveTime() < 3.8f)
	{
		BossGrenadeRenderer->Off();
		GameEngineRandom Random;

		// 이동 위치 랜덤 설정
		for (int i = 0; i < 50; i++)
		{
			int RandomPosX = Random.RandomInt(-110, 110);
			int RandomPosY = Random.RandomInt(-130, 130);

			std::shared_ptr<FX_Explosion> EnemyNewBullet = GetLevel()->CreateActor<FX_Explosion>(static_cast<int>(ContentsRenderType::Play));
			EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + RandomPosX, Transform.GetLocalPosition().Y + RandomPosY });
		}

		BossGrenadeAreaCollision->On();
		// 여기에서 플레이어 또는 보스 피격

	}

	if (GetLiveTime() > 4.0f)
	{
		Death();
	}
}