#include "PreCompile.h"
#include <GameEngineCore/GameEngineState.h>
#include "Enemy.h"
#include "Player.h"

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
		DirCheck();

		EnemyDetectEvent();

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

		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

		Transform.AddWorldPosition(PlayerChasePos * _Delta);

		// �÷��̾� ��ġ���� ���� �Ÿ��� ���ߴ� �������� �۰ų� ������
		if (PlayerChasePos.X <= 200.0f)
		{
			// ���� ���·� �����մϴ�.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
			return;
		}
		// �÷��̾���� �Ÿ��� ����ġ���� �־��� ���
		else if (PlayerChasePos.X > 400.0f)
		{
			// ��� ���·� �����մϴ�.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
		}
	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Chase, EnemyState_Chase_Param);
}

void Enemy::FSM_Enemy_Death()
{
	CreateStateParameter EnemyState_Death_Param;

	EnemyState_Death_Param.Start = [=](class GameEngineState* _Parent)
	{
		EnemyMainRenderer->ChangeAnimation("Death");
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
		EnemyMainRenderer->ChangeAnimation("Attack");
	};

	EnemyState_Attack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// ���� ���� ���� ���� �޾� Death ó�� �Ǹ� �Ʒ� ������ �������� �ʰ� �ٷ� Death ���·� ��ȯ�մϴ�.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		// Idle ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);
		DirCheck();

		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

		// �Ÿ��� �־�����
		if (PlayerChasePos.X > 200.0f || PlayerChasePos.X < -200.0f)
		{
			// �߰� ���·� �����մϴ�.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Chase);
			return;
		}
	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Attack, EnemyState_Attack_Param);
}