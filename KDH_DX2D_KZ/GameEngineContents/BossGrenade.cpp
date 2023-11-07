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

	BossGrenadeCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyAttack);
	BossGrenadeCollision->SetCollisionType(ColType::SPHERE2D);
	BossGrenadeCollision->Transform.SetLocalScale({ 20.0f, 20.0f });

	GameEngineRandom Random;

	// �̵� ��ġ ���� ����
	int Count = Random.RandomInt(0, 2);
	switch (Count)
	{
	case 0:
		SetGrenadeSpeed(10.0f);
		break;

	case 1:
		SetGrenadeSpeed(20.0f);
		break;

	case 2:
		SetGrenadeSpeed(30.0f);
		break;

	default:
		break;
	}

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

		// ��
		if (-204.0f < Transform.GetLocalPosition().Y && false == IsOnCurve)
		{
			IsOnCurve = true;
			MovePos = { (float4::LEFT + float4::DOWN) * 300.0f * _Delta * coef_res };
		}
		else if(false == IsOnCurve)
		{
			MovePos = { (float4::LEFT + float4::UP) * 300.0f * _Delta };
		}

		// �Ʒ�
		if (-480.0f > Transform.GetLocalPosition().Y)
		{
			MovePos = { (float4::LEFT + float4::UP) * 300.0f * _Delta * coef_res };
		}

		// ������
		if (1128.0f < Transform.GetLocalPosition().X)
		{
			MovePos = { (float4::LEFT + float4::DOWN) * 300.0f * _Delta * coef_res };
		}

		// ����
		if (160.0f > Transform.GetLocalPosition().X)
		{
			MovePos = { (float4::RIGHT) * 300.0f * _Delta * coef_res };
		}




			//float4 CheckPos = { Transform.GetWorldPosition() + UpCheck };

			//GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

			//if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
			//{
			//	MovePos = { (float4::LEFT + float4::UP) * 300.0f * _Delta };
			//}
			//else
			//{
			//	MovePos = float4::ZERO;
			//}

//		}

		//if (true == IsOnCurve)
		//{

		//	float4 CheckPos = { Transform.GetWorldPosition() + LeftCheck + DownCheck };

		//	GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		//	if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
		//	{
		//		MovePos = { (float4::LEFT + float4::DOWN) * 300.0f * _Delta };
		//	}
		//	else
		//	{

		//	}

		//}

		Transform.AddLocalPosition(MovePos);

		//		Transform.AddLocalPosition({ -1.0f * _Delta * 200.0f, 1.0f * _Delta * 200.0f });
	}


	if (GetLiveTime() > 2.0f)
	{
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

		// �̵� ��ġ ���� ����
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