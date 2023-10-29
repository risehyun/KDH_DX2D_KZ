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
		// ���� ���� ���� ���� �޾� Death ó�� �Ǹ� �Ʒ� ������ �������� �ʰ� �ٷ� Death ���·� ��ȯ�մϴ�.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		// Idle ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);

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
		// ���� ���� ���� ���� �޾� Death ó�� �Ǹ� 
		if (true == IsEnemyDeath)
		{
			// �Ʒ� ������ �������� �ʰ� �ٷ� Death ���·� ��ȯ�մϴ�.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		Gravity(_Delta);
		DirCheck();

		float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
		float4 Enemypos = Transform.GetWorldPosition();
		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

		OutputDebugStringA(PlayerChasePos.ToString("\n").c_str());

		//	PlayerChasePos.Normalize();


		if(false == GetGroundPixelCollision())
		{
			Transform.AddWorldPosition(PlayerChasePos * _Delta/* * Speed*/);
		}



		// �ٰŸ�, ���Ÿ� Enemy ���� ������
		if (Type == EnemyType::ShieldCop)
		{

			// �÷��̾� ��ġ���� ���� �Ÿ��� ���ߴ� �������� �۰ų� ������
			if ((PlayerChasePos.X > 0.0f && PlayerChasePos.X <= 70.0f) && (PlayerChasePos.Y > -2.0f && PlayerChasePos.Y < 2.0f)
				|| (PlayerChasePos.X < 0.0f && PlayerChasePos.X >= -70.0f) && (PlayerChasePos.Y > -2.0f && PlayerChasePos.Y < 2.0f))
			{
				// ���� ���·� �����մϴ�.
				FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
				return;
			}
		}
		else
		{
			// �÷��̾� ��ġ���� ���� �Ÿ��� ���ߴ� �������� �۰ų� ������
			if ((PlayerChasePos.X > 0.0f && PlayerChasePos.X <= 200.0f) && (PlayerChasePos.Y > -10.0f && PlayerChasePos.Y < 10.0f)
				|| (PlayerChasePos.X < 0.0f && PlayerChasePos.X >= -200.0f) && (PlayerChasePos.Y > -10.0f && PlayerChasePos.Y < 10.0f))
			{
				// ���� ���·� �����մϴ�.
				FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
				return;
			}
		}



		// �÷��̾���� �Ÿ��� ����ġ���� �־��� ���
		if (PlayerChasePos.X > 600.0f)
		{
			// ��� ���·� �����մϴ�.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
			return;
		}
	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Chase, EnemyState_Chase_Param);
}

void Enemy::FSM_Enemy_Death()
{
	CreateStateParameter EnemyState_Death_Param;

	EnemyState_Death_Param.Start = [=](class GameEngineState* _Parent)
	{
		IsEnemyDeath = true;
		EnemyMainRenderer->ChangeAnimation("Death");
		ChangeEmotion(EEnemyState_Emotion::Default);

		// ���� ���¿����� ���̻� �浹 �ۿ��� �Ͼ�� �ʵ��� �浹ü�� ���ݴϴ�.
		EnemyDetectCollision->Off();
		EnemyMainCollision->Off();

		--GameStateManager::GameState->LeftEnemy;
	};

	EnemyState_Death_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		Gravity(_Delta);
	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Death, EnemyState_Death_Param);
}

void Enemy::FSM_Enemy_Attack()
{
	CreateStateParameter EnemyState_Attack_Param;

	EnemyState_Attack_Param.Start = [=](class GameEngineState* _Parent)
	{
		// ���� Enemy�� ���� üũ(�ͷ��� ��� ���� ��ȯ�� ���� �����Ƿ� ����)
		if (Type != EnemyType::FloorTurrent)
		{
			DirCheck();
		}


		if (Dir == EnemyDir::Right)
		{
			AttackFireInitPos = { Transform.GetWorldPosition().X + 70.0f, Transform.GetWorldPosition().Y + 10.0f };
			EnemyEffectRenderer->Transform.SetLocalPosition({ 70.0f, 10.0f });
			AttackFireDir = float4::RIGHT;
		}
		else // ���Ÿ� ������ �ϴ� Enemy�� ���
		{
			EnemyEffectRenderer->ChangeAnimation("GunSpark", true);
			EnemyEffectRenderer->On();

			AttackFireInitPos = { Transform.GetWorldPosition().X - 70.0f, Transform.GetWorldPosition().Y + 10.0f };
			EnemyEffectRenderer->Transform.SetLocalPosition({ -70.0f, 10.0f });
			AttackFireDir = float4::LEFT;
		}


		EnemyMainRenderer->ChangeAnimation("Attack");
	

		// �ٰŸ� Enemy
		if (Type != EnemyType::ShieldCop)
		{
			// Bullet ����
			std::shared_ptr<Bullet> EnemyNewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(ContentsRenderType::Play));
			EnemyNewBullet->InitBulletData(ContentsCollisionType::EnemyAttack, AttackFireDir, 3.0f, true);

			if (Type == EnemyType::FloorTurrent)
			{
				AttackFireInitPos = { Transform.GetWorldPosition().X + 70.0f, Transform.GetWorldPosition().Y + 17.0f };
			}

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

		// ���� ���� ���� ���� �޾� Death ó�� �Ǹ� �Ʒ� ������ �������� �ʰ� �ٷ� Death ���·� ��ȯ�մϴ�.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}



		// Idle ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);

		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();


		if (EnemyMainRenderer->IsCurAnimationEnd())
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
			return;
		}


		if (Type != EnemyType::FloorTurrent)
		{
			// �Ÿ��� �־�����
			if (PlayerChasePos.X > 200.0f || PlayerChasePos.X < -200.0f)
			{
				// �߰� ���·� �����մϴ�.
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