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
		// 만약 상태 도중 공격 받아 Death 처리 되면 아래 로직을 실행하지 않고 바로 Death 상태로 전환합니다.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		// Idle 상태인 동안에는 중력이 작용합니다.
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
		// 만약 상태 도중 공격 받아 Death 처리 되면 
		if (true == IsEnemyDeath)
		{
			// 아래 로직을 실행하지 않고 바로 Death 상태로 전환합니다.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		Gravity(_Delta);
		DirCheck();

		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

		Transform.AddWorldPosition(PlayerChasePos * _Delta);

		// 플레이어 위치까지 남은 거리가 멈추는 지점보다 작거나 같으면
		if (PlayerChasePos.X <= 200.0f)
		{
			// 공격 상태로 변경합니다.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
			return;
		}
		// 플레이어와의 거리가 기준치보다 멀어진 경우
		else if (PlayerChasePos.X > 400.0f)
		{
			// 대기 상태로 변경합니다.
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
		// 만약 상태 도중 공격 받아 Death 처리 되면 아래 로직을 실행하지 않고 바로 Death 상태로 전환합니다.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		// Idle 상태인 동안에는 중력이 작용합니다.
		Gravity(_Delta);
		DirCheck();

		PlayerChasePos = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

		// 거리가 멀어지면
		if (PlayerChasePos.X > 200.0f || PlayerChasePos.X < -200.0f)
		{
			// 추격 상태로 변경합니다.
			FSM_EnemyState.ChangeState(FSM_EnemyState::Chase);
			return;
		}
	};

	FSM_EnemyState.CreateState(FSM_EnemyState::Attack, EnemyState_Attack_Param);
}