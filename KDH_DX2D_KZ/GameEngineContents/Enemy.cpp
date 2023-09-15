#include "PreCompile.h"
#include "Enemy.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
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
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		EnemyMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		EnemyMainRenderer->CreateAnimation("Idle", "spr_gangsteridle");
		EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);

		EnemyMainRenderer->AutoSpriteSizeOn();
	}

	EnemyMainRenderer->ChangeAnimation("Idle");

	EnemyMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	EnemyMainCollision->Transform.SetLocalScale({ 30, 30, 1 });
}

void Enemy::Update(float _Delta)
{

	StateUpdate(_Delta);



	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(thisActor);

		EnemyPtr->ChangeState(EnemyState::Death);
	};

	Event.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		int a = 0;
	};


	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

	};

	EnemyMainCollision->CollisionEvent(ContentsCollisionType::Player, Event);
}
