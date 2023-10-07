#include "PreCompile.h"
#include "Enemy.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "Bullet.h"

Enemy::Enemy()
{
	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	int a = 0;

}

Enemy::Enemy(EnemyType _Type)
{
	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	Type = _Type;

	int a = 0;
}


Enemy::~Enemy()
{
}

void Enemy::InitEnemyData()
{
	{
		EnemyMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		EnemyMainRenderer->AutoSpriteSizeOn();


		if (Type == EnemyType::NormalGangster)
		{
			EnemyMainRenderer->CreateAnimation("Idle", "spr_gangsteridle");
			EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);

			EnemyMainRenderer->ChangeAnimation("Idle");
		}


		if (Type == EnemyType::ColoredGangster)
		{
			EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground2", 0.2f, 0, 5, false);
			EnemyMainRenderer->ChangeAnimation("Death");
		}

	}

	{
		EnemyEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		EnemyEffectRenderer->Transform.SetLocalPosition({ 70.0f, -4.f, 0.f, 1.f });

		EnemyEffectRenderer->CreateAnimation("GunSpark", "spr_gunspark");
		EnemyEffectRenderer->AutoSpriteSizeOn();


		EnemyEffectRenderer->ChangeAnimation("GunSpark");

	}

	EnemyMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyBody);
	EnemyMainCollision->Transform.SetLocalScale({ 30, 30, 1 });

}

void Enemy::SetEnemyData(EnemyType _EnemyType)
{
	Type = _EnemyType;

	InitEnemyData();
}

void Enemy::ChangeState(EnemyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case EnemyState::Idle:
			IdleStart();
			break;

		case EnemyState::Run:
			RunStart();
			break;

		case EnemyState::Attack:
			AttackStart();
			break;

		case EnemyState::Death:
			DeathStart();
			break;

		default:
			break;
		}
	}

	State = _State;

}

void Enemy::StateUpdate(float _Delta)
{
	switch (State)
	{
	case EnemyState::Idle:
		return IdleUpdate(_Delta);

	case EnemyState::Run:
		return RunUpdate(_Delta);

	case EnemyState::Attack:
		return AttackUpdate(_Delta);

	case EnemyState::Death:
		return DeathUpdate(_Delta);

	default:
		break;
	}
}

void Enemy::DirCheck()
{
}

void Enemy::ChangeAnimationState(std::string_view _StateName)
{
}

void Enemy::IdleStart()
{
}

void Enemy::IdleUpdate(float _Delta)
{
}

void Enemy::RunStart()
{
}

void Enemy::RunUpdate(float _Delta)
{
}

void Enemy::AttackStart()
{
}

void Enemy::AttackUpdate(float _Delta)
{
}

void Enemy::DeathStart()
{
	EnemyMainRenderer->ChangeAnimation("Death");
}

void Enemy::DeathUpdate(float _Delta)
{

	if (true == EnemyMainRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}

void Enemy::Start()
{

	/*{
		EnemyMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		EnemyMainRenderer->AutoSpriteSizeOn();


		if (Type == EnemyType::NormalGangster)
		{
			EnemyMainRenderer->CreateAnimation("Idle", "spr_gangsteridle");
			EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);

			EnemyMainRenderer->ChangeAnimation("Idle");
		}


		if (Type == EnemyType::ColoredGangster)
		{
			EnemyMainRenderer->CreateAnimation("Death_ColoredGangster", "spr_gangsterhurtground2", 0.2f, 0, 5, false);
			EnemyMainRenderer->ChangeAnimation("Death_ColoredGangster");
		}

	}

	{
		EnemyEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		EnemyEffectRenderer->Transform.SetLocalPosition({ 70.0f, -4.f, 0.f, 1.f });

		EnemyEffectRenderer->CreateAnimation("GunSpark", "spr_gunspark");
		EnemyEffectRenderer->AutoSpriteSizeOn();


		EnemyEffectRenderer->ChangeAnimation("GunSpark");

	}

	EnemyMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyBody);
	EnemyMainCollision->Transform.SetLocalScale({ 30, 30, 1 });*/

	{
		std::shared_ptr<Bullet> EnemyNewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(ContentsRenderType::Play));
		EnemyNewBullet->InitBulletData(ContentsCollisionType::EnemyAttack, float4::RIGHT);
		EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetWorldPosition().X - 80.f, Transform.GetWorldPosition().Y + 82.f });

	}

}

void Enemy::Update(float _Delta)
{

	StateUpdate(_Delta);

	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(thisActor);

		GameEngineActor* PlayerAttackActor = Col->GetActor();
		Col->Death();

		EnemyPtr->ChangeState(EnemyState::Death);
	};

	EnemyMainCollision->CollisionEvent(ContentsCollisionType::PlayerAttack, Event);
}
