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
			// 만약 상태 도중 공격 받아 Death 처리 되면 아래 로직을 실행하지 않고 바로 Death 상태로 전환합니다.
			//if (true == IsEnemyDeath)
			//{
			//	FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			//	return;
			//}

			if (GameEngineInput::IsDown('1', this))
			{
				FSM_BossState.ChangeState(FSM_BossState::GroundRifleAttack_Start);
				return;
			}

			if (GameEngineInput::IsDown('2', this))
			{
				FSM_BossState.ChangeState(FSM_BossState::AirRifleAttack_Start);
			}

			// Idle 상태인 동안에는 중력이 작용합니다.
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
				FSM_BossState.ChangeState(FSM_BossState::GroundRifleAttack_End);
				return;
			}

		};

	FSM_BossState.CreateState(FSM_BossState::GroundRifleAttack_Start, BossState_GroundRifleAttack_Param);
}

void Boss::FSM_Boss_GroundRifleAttackEnd()
{
	CreateStateParameter BossState_GroundRigleAttackEnd_Param;

	BossState_GroundRigleAttackEnd_Param.Start = [=](class GameEngineState* _Parent)
		{
			BossMainRenderer->ChangeAnimation("PutBackRifle");
		};

	BossState_GroundRigleAttackEnd_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
		{
			if (BossMainRenderer->IsCurAnimationEnd())
			{
				FSM_BossState.ChangeState(FSM_BossState::Idle);
				return;
			}
		};

	FSM_BossState.CreateState(FSM_BossState::GroundRifleAttack_End, BossState_GroundRigleAttackEnd_Param);
}

void Boss::FSM_Boss_AirRifleAttack()
{
	CreateStateParameter BossState_AirRifleAttack_Param;

	BossState_AirRifleAttack_Param.Start = [=](class GameEngineState* _Parent)
		{
			BossMainRenderer->ChangeAnimation("Sweep");
			BossMainRenderer->RightFlip();

			GameEngineRandom Random;

			// 이동 위치 랜덤 설정
			int Count = Random.RandomInt(0, 2);
			switch (Count)
			{
				// 중앙
			case 0:
				Transform.SetLocalPosition({ 550, -250 });
				break;

				// 왼쪽
			case 1:
				Transform.SetLocalPosition({ 250, -250 });
				break;

				// 오른쪽
			case 2:
				Transform.SetLocalPosition({ 1000, -250 });
				break;

			default:
				break;
			}

			std::shared_ptr<BossLaser> EnemyNewBullet = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

			EnemyNewBullet->InitBossLaserData(BossLaserType::Rot, float4::DOWN, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f });
		};

	BossState_AirRifleAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
		{
			if (BossMainRenderer->IsCurAnimationEnd())
			{
				FSM_BossState.ChangeState(FSM_BossState::Idle);
				return;
			}
		};

	FSM_BossState.CreateState(FSM_BossState::AirRifleAttack_Start, BossState_AirRifleAttack_Param);
}

void Boss::FSM_Boss_AirRifleAttackEnd()
{
	CreateStateParameter BossState_AirRifleAttackEnd_Param;

	BossState_AirRifleAttackEnd_Param.Start = [=](class GameEngineState* _Parent)
		{
			BossMainRenderer->ChangeAnimation("PutBackRifle");
		};

	BossState_AirRifleAttackEnd_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
		{

			if (BossMainRenderer->IsCurAnimationEnd())
			{
				FSM_BossState.ChangeState(FSM_BossState::Idle);
				return;
			}


		};

	FSM_BossState.CreateState(FSM_BossState::AirRifleAttack_End, BossState_AirRifleAttackEnd_Param);
}
