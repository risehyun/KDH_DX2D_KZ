#include "PreCompile.h"
#include "Boss.h"

#include <GameEngineCore/GameEngineState.h>
#include "BossLaser.h"
#include "Player.h"
#include "BossBullet.h"

void Boss::FSM_Boss_Idle()
{
	CreateStateParameter BossState_Idle_Param;

	BossState_Idle_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("Idle");
	};

	BossState_Idle_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		// Idle ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);

		// ���� ���� ���� ���� �޾� Death ó�� �Ǹ� �Ʒ� ������ �������� �ʰ� �ٷ� Death ���·� ��ȯ�մϴ�.
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

		if (GameEngineInput::IsDown('4', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::GroundDashAttack);
			return;
		}

		if (GameEngineInput::IsDown('5', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::WallJumpAttack);
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
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::LEFT, { this->Transform.GetLocalPosition().X - 550.0f, Transform.GetLocalPosition().Y + 14.0f }, float4::ZERO);
		}
		else
		{
			EnemyNewBullet->InitBossLaserData(BossLaserType::Normal, float4::RIGHT, { this->Transform.GetLocalPosition().X + 550.0f, Transform.GetLocalPosition().Y + 14.0f }, float4::ZERO);
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

		// �̵� ��ġ ���� ����
		int Count = Random.RandomInt(0, 2);
		switch (Count)
		{
			// �߾�
		case 0:
			Transform.SetLocalPosition({ 550, -250 });
			break;

			// ����
		case 1:
			Transform.SetLocalPosition({ 250, -250 });
			break;

			// ������
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

		BossNewLaser->InitBossLaserData(BossLaserType::Rot, float4::DOWN, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);

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
		// ù��°
		Transform.SetLocalPosition({ 200, -180 });
		BossMainRenderer->ChangeAnimation("TeleportIn");

		std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
		BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
		BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
	};

	BossState_MultipleAirRifleAttackStart_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (FSM_BossState.GetStateTime() > 0.5f && FSM_BossState.GetStateTime() < 0.6f)
		{
			Transform.SetLocalPosition({ 1080, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.0f && FSM_BossState.GetStateTime() < 1.1f)
		{
			Transform.SetLocalPosition({ 330, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.5f && FSM_BossState.GetStateTime() < 1.6f)
		{
			Transform.SetLocalPosition({ 940, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
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

void Boss::FSM_Boss_GroundDashAttack()
{
	CreateStateParameter BossState_GroundDashAttack_Param;

	BossState_GroundDashAttack_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();

		BossMainRenderer->ChangeAnimation("PreDash");

		float4 PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();
		Dis = PlayerPos - Transform.GetLocalPosition();

		if (Dir == BossDir::Left)
		{
			Dis.X = Dis.X - 8.0f;
		}
		else
		{
			Dis.X = Dis.X + 8.0f;
		}

		// ���� ���� ���
		float4 RenderLinePos = Transform.GetLocalPosition();

		float4 angle = atan2(RenderLinePos.Y - PlayerPos.Y,
			RenderLinePos.X - PlayerPos.X);

		float4 ToPlayer = Dis;
		ToPlayer.Size();

		std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		// ������ ����� ���� ���� ������ ����մϴ�.
		BossNewLaser->InitBossLaserData(BossLaserType::Red, float4::ZERO, RenderLinePos, float4::ZERO);
		BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		BossNewLaser->BossLaserRenderer->Transform.SetLocalScale({ ToPlayer.Size() / 2.0f, 1.0f, 1.0f });
		BossNewLaser->BossLaserRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });
		BossNewLaser->BossLaserRenderer->Transform.SetLocalPosition(RenderLinePos);
	};

	BossState_GroundDashAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimation("PreDash")
			&& BossMainRenderer->IsCurAnimationEnd())
		{
			BossMainRenderer->ChangeAnimation("Dash");
		}

		if (BossMainRenderer->IsCurAnimation("Dash"))
		{
			if (Dir == BossDir::Left)
			{
				CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			}
			else
			{
				CheckPos = { Transform.GetWorldPosition() + RightCheck };
			}

			GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

			if (Color == GameEngineColor::WHITE)
			{
				Transform.AddLocalPosition(Dis * _Delta * 1.5f);
			}
			else
			{
				BossMainRenderer->ChangeAnimation("DashEnd");
			}

			if (FSM_BossState.GetStateTime() > 2.0f)
			{
				BossMainRenderer->ChangeAnimation("DashEnd");
			}
		}

		if (BossMainRenderer->IsCurAnimation("DashEnd")
			&& BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::GroundDashAttack, BossState_GroundDashAttack_Param);
}

void Boss::FSM_Boss_WallJump()
{
	CreateStateParameter BossState_WallJump_Param;

	BossState_WallJump_Param.Start = [=](class GameEngineState* _Parent)
	{
	//	BossMainRenderer->ChangeAnimation("WallJump");
	//	BossMainRenderer->ChangeAnimation("Idle");
		AttackFireInitPos = { Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y + 30.0f };

	};

	BossState_WallJump_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		


		static float timer = 2.1f;

		timer += _Delta;

		// GameEngineInput::IsDown(VK_TAB, this)
		if (timer > 2.1f)
		{
			BossMainRenderer->ChangeAnimation("WallJump");
			//for (int i = 0; i < 15; i++)
			//{

				//			DirCheck();
			
			for (int i = 0; i < 15; i++)
			{
				std::shared_ptr<BossBullet> BossNewBullet = GetLevel()->CreateActor<BossBullet>(static_cast<int>(ContentsRenderType::Play));
			

				BossNewBullet->Transform.SetLocalPosition(AttackFireInitPos);


				Transform.AddLocalRotation({ 0.0f, 0.0f, 1.0f * _Delta * 400.0f });

				float4 direction = { cosf(fireAngle * GameEngineMath::D2R), sinf(fireAngle * GameEngineMath::D2R) };

				BossNewBullet->Transform.AddLocalRotation(Transform.GetLocalRotationEuler());
				BossNewBullet->Transform.AddLocalPosition(Transform.GetLocalPosition() * float4::RIGHT * _Delta);


				BossNewBullet->Transform.SetWorldPosition(Transform.GetWorldPosition());

				BossNewBullet->MovePos = direction;

				//�߻��� ������ ������ ���ݰ�(angleInterval)�� ���� ����
				fireAngle += angleInterval;

				if (fireAngle > 360) fireAngle -= 360;
				//0~360��

				timer = 0.0f;
			}
		//	}


//
//			for (int fireAngle = startAngle; fireAngle < endAngle; fireAngle += angleInterval)
//			{
//				std::shared_ptr<BossBullet> BossNewBullet = GetLevel()->CreateActor<BossBullet>(static_cast<int>(ContentsRenderType::Play));
//				float4 direction = { cosf(fireAngle * GameEngineMath::D2R), sinf(fireAngle * GameEngineMath::D2R) };
//				
//				BossNewBullet->Transform.SetLocalPosition(Transform.GetLocalPosition());
//
//				BossNewBullet->MovePos = direction;
//
////				BossNewBullet->Transform.AddLocalPosition(direction * 200.0f);
//
//				fireAngle += angleInterval;
//				//�߻��� ������ ������ ���ݰ�(angleInterval)�� ���� ����
//				if (fireAngle > 360) fireAngle -= 360;
//
//			}













			//for (int i = 0; i < 10; i++)
			//{
			//	std::shared_ptr<BossBullet> EnemyNewBullet = GetLevel()->CreateActor<BossBullet>(static_cast<int>(ContentsRenderType::Play));
			//	//EnemyNewBullet->InitBulletData(ContentsCollisionType::EnemyAttack, float4::DOWN, 5.0f);

			//	EnemyNewBullet->Transform.SetLocalPosition(Transform.GetLocalPosition());

			//	EnemyNewBullet->Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * i / 10.0f - 90.0f });
			//	EnemyNewBullet->Transform.AddLocalPosition({ 200.0f * cosf(GameEngineMath::PI * 2 * i / 10), 200.0f * sinf(GameEngineMath::PI * 2 * i / 10) });
			//
			//}




			// Keep
			/*
			AttackFireInitPos = { Transform.GetWorldPosition().X + 70.0f, Transform.GetWorldPosition().Y + 17.0f };

			std::shared_ptr<BossBullet> BossNewBullet = GetLevel()->CreateActor<BossBullet>(static_cast<int>(ContentsRenderType::Play));
			BossNewBullet->Transform.SetLocalPosition(AttackFireInitPos);
			*/






			//EnemyNewBullet->InitBulletData(ContentsCollisionType::EnemyAttack, float4::DOWN, 5.0f);
		
		
			//Transform.AddLocalRotation({ 0.0f, 0.0f, 1.0f * _Delta * 400.0f });

			//EnemyNewBullet->Transform.AddLocalRotation(Transform.GetLocalRotationEuler() * 2.0f);
			//EnemyNewBullet->Transform.AddLocalPosition(Transform.GetLocalPosition() * float4::UP * _Delta);


			//timer = 0.0f;
		}


		//if (BossMainRenderer->IsCurAnimationEnd())
		//{
		//	FSM_BossState.ChangeState(FSM_BossState::Idle);
		//	return;
		//}
	};

	FSM_BossState.CreateState(FSM_BossState::WallJumpAttack, BossState_WallJump_Param);
}
