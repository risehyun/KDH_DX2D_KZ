#include "PreCompile.h"
#include "Boss.h"

#include <GameEngineCore/GameEngineState.h>
#include "BossLaser.h"

void Boss::FSM_Boss_Idle()
{
	CreateStateParameter BossState_Idle_Param;

	BossState_Idle_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("Idle");
	};

	BossState_Idle_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// ���� ���� ���� ���� �޾� Death ó�� �Ǹ� �Ʒ� ������ �������� �ʰ� �ٷ� Death ���·� ��ȯ�մϴ�.
		//if (true == IsEnemyDeath)
		//{
		//	FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
		//	return;
		//}

		// Idle ������ ���ȿ��� �߷��� �ۿ��մϴ�.
	//	Gravity(_Delta);

	};

	FSM_BossState.CreateState(FSM_BossState::Idle, BossState_Idle_Param);
}

void Boss::FSM_Boss_GroundRifleAttack()
{
	CreateStateParameter BossState_GroundRifleAttack_Param;

	BossState_GroundRifleAttack_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("TakeOutRifle");

		DirCheck();

		std::shared_ptr<BossLaser> EnemyNewBullet = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		if (Dir == BossDir::Left)
		{
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::LEFT, { Transform.GetLocalPosition().X - 550.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
		else
		{
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::RIGHT, { Transform.GetLocalPosition().X + 550.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
	};

	BossState_GroundRifleAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (FSM_BossState.GetStateTime() > 2.0f)
		{
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}

	};

	FSM_BossState.CreateState(FSM_BossState::GroundRifleAttack, BossState_GroundRifleAttack_Param);
}