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

		// Idle 상태인 동안에는 중력이 작용합니다.
		Gravity(_Delta);

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
			return;
		}

		if (GameEngineInput::IsDown('3', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::MultipleAirRifleAttack_Start);
			return;
		}

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
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::LEFT, { this->Transform.GetLocalPosition().X - 550.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
		else
		{
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::RIGHT, { this->Transform.GetLocalPosition().X + 550.0f, Transform.GetLocalPosition().Y + 14.0f });
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

void Boss::FSM_Boss_AirRifleAttack_Start()
{
	CreateStateParameter BossState_AirRifleAttackStart_Param;

	BossState_AirRifleAttackStart_Param.Start = [=](class GameEngineState* _Parent)
	{
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

		BossMainRenderer->ChangeAnimation("SweepTeleportIn");
	};

	BossState_AirRifleAttackStart_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::AirRifleAttack);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::AirRifleAttack_Start, BossState_AirRifleAttackStart_Param);

}

void Boss::FSM_Boss_AirRifleAttack()
{
	CreateStateParameter BossState_AirRifleAttack_Param;

	BossState_AirRifleAttack_Param.Start = [=](class GameEngineState* _Parent)
	{
		std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		BossNewLaser->InitBossLaserData(BossLaserType::Rot, float4::DOWN, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f });

		BossMainRenderer->ChangeAnimation("Sweep");
	};

	BossState_AirRifleAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::AirRifleAttack_End);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::AirRifleAttack, BossState_AirRifleAttack_Param);
}

void Boss::FSM_Boss_AirRifleAttackEnd()
{
	CreateStateParameter BossState_AirRifleAttackEnd_Param;

	BossState_AirRifleAttackEnd_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("SweepTeleportOut");
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

void Boss::FSM_Boss_MultipleAirRifleAttack()
{
	CreateStateParameter BossState_MultipleAirRifleAttackStart_Param;

	BossState_MultipleAirRifleAttackStart_Param.Start = [=](class GameEngineState* _Parent)
	{
		
		// 첫번째
		Transform.SetLocalPosition({ 200, -180 });
		//Transform.SetLocalPosition({ 1000, -180 });

		BossMainRenderer->ChangeAnimation("TeleportIn");

		std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
		BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f });
		BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
	};

	BossState_MultipleAirRifleAttackStart_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (FSM_BossState.GetStateTime() > 0.5f && FSM_BossState.GetStateTime() < 0.6f)
		{
			Transform.SetLocalPosition({ 1080, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f });
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.0f && FSM_BossState.GetStateTime() < 1.1f)
		{
			Transform.SetLocalPosition({ 330, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f });
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.5f && FSM_BossState.GetStateTime() < 1.6f)
		{
			Transform.SetLocalPosition({ 940, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f });
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 2.0f)
		{
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}

	};

	FSM_BossState.CreateState(FSM_BossState::MultipleAirRifleAttack_Start, BossState_MultipleAirRifleAttackStart_Param);

}
