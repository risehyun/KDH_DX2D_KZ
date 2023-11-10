#include "PreCompile.h"
#include <GameEngineCore/GameEngineState.h>
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "GameStateManager.h"
#include "Attack.h"

void Enemy::FSM_Enemy_Idle()
{
	CreateStateParameter EnemyState_Idle_Param;

	EnemyState_Idle_Param.Start = [=](class GameEngineState* _Parent)
	{
		EnemyMainRenderer->ChangeAnimation("Idle");
	};

	EnemyState_Idle_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// 만약 상태 도중 공격 받아 Death 처리 되면 아래 로직을 실행하지 않고 바로 Death 상태로 전환합니다.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		else if (Type != EnemyType::WallTurret)
		{
			// Idle 상태인 동안에는 중력이 작용합니다.
			Gravity(_Delta);

		}

		EnemyPlayerDetectEvent();

	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Idle, EnemyState_Idle_Param);
}

void Enemy::FSM_Enemy_Chase()
{
	CreateStateParameter EnemyState_Chase_Param;

	EnemyState_Chase_Param.Start = [=](class GameEngineState* _Parent)
	{
		EnemyMainRenderer->ChangeAnimation("Run");
	};

	EnemyState_Chase_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// 만약 상태 도중 공격 받아 Death 처리 되면 
		if (true == IsEnemyDeath)
		{
			// 아래 로직을 실행하지 않고 바로 Death 상태로 전환합니다.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		Gravity(_Delta);
		DirCheck();

		float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
		float4 Enemypos = Transform.GetWorldPosition();
		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

	//	OutputDebugStringA(PlayerChasePos.ToString("\n").c_str());

		//// 지면에 있는 경우
		//if(false == GetGroundPixelCollision())
		//{
		//	Transform.AddWorldPosition(PlayerChasePos * _Delta);
		//}
		

	CheckPos = { Transform.GetWorldPosition() + LeftCheck };

	GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);


	if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
	{
		Transform.AddWorldPosition(PlayerChasePos * _Delta);
	}
	else
	{
		Transform.AddWorldPosition(float4::UP + PlayerChasePos * _Delta);
	}

		// 근거리, 원거리 Enemy 따로 나누기
		if (Type == EnemyType::ShieldCop)
		{

			// 플레이어 위치까지 남은 거리가 멈추는 지점보다 작거나 같으면
			if ((PlayerChasePos.X > 0.0f && PlayerChasePos.X <= 70.0f) && (PlayerChasePos.Y > -2.0f && PlayerChasePos.Y < 2.0f)
				|| (PlayerChasePos.X < 0.0f && PlayerChasePos.X >= -70.0f) && (PlayerChasePos.Y > -2.0f && PlayerChasePos.Y < 2.0f))
			{
				// 공격 상태로 변경합니다.
				FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
				return;
			}
		}
		else
		{
			// 플레이어 위치까지 남은 거리가 멈추는 지점보다 작거나 같으면
			if ((PlayerChasePos.X > 0.0f && PlayerChasePos.X <= 200.0f) && (PlayerChasePos.Y > -10.0f && PlayerChasePos.Y < 10.0f)
				|| (PlayerChasePos.X < 0.0f && PlayerChasePos.X >= -200.0f) && (PlayerChasePos.Y > -10.0f && PlayerChasePos.Y < 10.0f))
			{
				// 공격 상태로 변경합니다.
				FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
				return;
			}
		}



		// 플레이어와의 거리가 기준치보다 멀어진 경우
		if (PlayerChasePos.X > 600.0f && Type != EnemyType::WallTurret)
		{
			// 대기 상태로 변경합니다.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
			return;
		}
	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Chase, EnemyState_Chase_Param);
}

void Enemy::FSM_Enemy_Appear()
{
	CreateStateParameter EnemyState_Appear_Param;

	EnemyState_Appear_Param.Start = [=](class GameEngineState* _Parent)
	{
		EnemyMainRenderer->ChangeAnimation("Appear");
	};

	EnemyState_Appear_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (true == EnemyMainRenderer->IsCurAnimationEnd())
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
			return;
		}

	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Appear, EnemyState_Appear_Param);
}

void Enemy::FSM_Enemy_Death()
{
	CreateStateParameter EnemyState_Death_Param;

	EnemyState_Death_Param.Start = [=](class GameEngineState* _Parent)
	{
		IsEnemyDeath = true;
		EnemyMainRenderer->ChangeAnimation("Death");
		ChangeEmotion(EEnemyState_Emotion::Default);

		// 죽은 상태에서는 더이상 충돌 작용이 일어나지 않도록 충돌체를 꺼줍니다.
		EnemyDetectCollision->Off();
		EnemyMainCollision->Off();

		--GameStateManager::GameState->LeftEnemy;
	};

	EnemyState_Death_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (Type != EnemyType::WallTurret)
		{
			Gravity(_Delta);
		}
	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Death, EnemyState_Death_Param);
}

void Enemy::FSM_Enemy_Attack()
{
	CreateStateParameter EnemyState_Attack_Param;

	EnemyState_Attack_Param.Start = [=](class GameEngineState* _Parent)
		{
			// 현재 Enemy의 방향 체크(터렛의 경우 방향 전환을 하지 않으므로 제외)
			if (Type != EnemyType::FloorTurret && Type != EnemyType::WallTurret)
		{
			DirCheck();
		}


		if (Dir == EnemyDir::Right)
		{
			AttackFireInitPos = { Transform.GetWorldPosition().X + 70.0f, Transform.GetWorldPosition().Y + 10.0f };
			EnemyEffectRenderer->Transform.SetLocalPosition({ 70.0f, 10.0f });
			AttackFireDir = float4::RIGHT;
		}
		else // 원거리 공격을 하는 Enemy인 경우
		{
			EnemyEffectRenderer->ChangeAnimation("GunSpark", true);
			EnemyEffectRenderer->On();

			AttackFireInitPos = { Transform.GetWorldPosition().X - 70.0f, Transform.GetWorldPosition().Y + 10.0f };
			EnemyEffectRenderer->Transform.SetLocalPosition({ -70.0f, 10.0f });
			AttackFireDir = float4::LEFT;
		}


		EnemyMainRenderer->ChangeAnimation("Attack", true);
	

		// 근거리 Enemy가 아닌 경우
		if (Type != EnemyType::ShieldCop)
		{
			EffectPlayer = GameEngineSound::SoundPlay("sound_gun_fire.wav");
			// Bullet 세팅
			std::shared_ptr<Bullet> EnemyNewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(ContentsRenderType::Play));
	
			// 라인 범위 계산
			float4 EnemyPos = Transform.GetLocalPosition();
			float4 PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();
			AttackFireDir = PlayerPos - EnemyPos;

			float4 angle = atan2(EnemyPos.Y - PlayerPos.Y,
				EnemyPos.X - PlayerPos.X);

			float t = abs(angle.X * GameEngineMath::R2D);
		
			EnemyNewBullet->Transform.SetLocalRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });

			if (Type == EnemyType::FloorTurret || Type == EnemyType::WallTurret)
			{
				AttackFireInitPos = { Transform.GetWorldPosition().X + 70.0f, Transform.GetWorldPosition().Y + 17.0f };
			}

			EnemyNewBullet->InitBulletData(ContentsCollisionType::EnemyAttack, AttackFireDir, 3.0f, true);

			EnemyNewBullet->Transform.SetWorldPosition(AttackFireInitPos);
		}

		else
		{
			std::shared_ptr<Attack> EnemyNewAttack = GetLevel()->CreateActor<Attack>(static_cast<int>(ContentsRenderType::Play));			
			EnemyNewAttack->InitAttackData(ContentsCollisionType::EnemyAttack, AttackFireDir, 3.0f, true);
			EnemyNewAttack->Transform.SetWorldPosition(AttackFireInitPos);
			
		}

		/*
		
		EnemyEffectRenderer->Transform.SetLocalPosition({ 70.0f, 10.0f });
		CopShotgun FirePos { Transform.GetWorldPosition().X + 70.0f, Transform.GetWorldPosition().Y + 10.0f}
		
		*/
		
	};

	EnemyState_Attack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (EnemyEffectRenderer->IsCurAnimationEnd())
		{
			EnemyEffectRenderer->Off();
		}

		// 만약 상태 도중 공격 받아 Death 처리 되면 아래 로직을 실행하지 않고 바로 Death 상태로 전환합니다.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		if (Type != EnemyType::WallTurret)
		{
			// WallTurret은 벽에 고정된 상태이므로 중력 적용을 하지 않습니다.
			Gravity(_Delta);

		}

		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();


		if (EnemyMainRenderer->IsCurAnimationEnd())
		{
			if (Type == EnemyType::FloorTurret)
			{
				FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
				return;
			}
			else
			{
				FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
				return;
			}

		}


		if (Type != EnemyType::FloorTurret && Type != EnemyType::WallTurret)
		{
			// 거리가 멀어지면
			if (PlayerChasePos.X > 200.0f || PlayerChasePos.X < -200.0f)
			{
				// 추격 상태로 변경합니다.
				FSM_EnemyState.ChangeState(FSM_EnemyState::Chase);
				return;
			}

			if (3.0f < _Parent->GetStateTime())
			{
				FSM_EnemyState.ChangeState(FSM_EnemyState::Chase);
				return;
			}
		}

	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Attack, EnemyState_Attack_Param);
}