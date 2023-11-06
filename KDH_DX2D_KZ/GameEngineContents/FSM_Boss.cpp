#include "PreCompile.h"
#include "Boss.h"

#include <GameEngineCore/GameEngineState.h>
#include "BossLaser.h"
#include "Player.h"
#include "BossBullet.h"
#include "BossGrenade.h"
#include "WallOpen.h"

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

		if (GameEngineInput::IsDown('4', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::GroundDashAttack);
			return;
		}

		if (GameEngineInput::IsDown('5', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::WallJumpAttack_Start);
			return;
		}

		if (GameEngineInput::IsDown('6', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::GrenadeAttack_Start);
			return;
		}

		if (GameEngineInput::IsDown('7', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::AirDashAttack);
			return;
		}

		if (GameEngineInput::IsDown('8', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::WallTurretAttack);
			return;
		}

		if (GameEngineInput::IsDown('9', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::SuicideBombingAttack_Start);
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
		// 첫번째
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
			BossMainRenderer->ChangeAnimation("TeleportIn", true);

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.0f && FSM_BossState.GetStateTime() < 1.1f)
		{
			Transform.SetLocalPosition({ 330, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn", true);

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.5f && FSM_BossState.GetStateTime() < 1.6f)
		{
			Transform.SetLocalPosition({ 940, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn", true);

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 2.0f)
		{
			BossMainRenderer->ChangeAnimation("TeleportOut");

			if (BossMainRenderer->IsCurAnimationEnd())
			{
				FSM_BossState.ChangeState(FSM_BossState::Idle);
				return;
			}
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

		// 라인 범위 계산
		float4 RenderLinePos = Transform.GetLocalPosition();

		float4 angle = atan2(RenderLinePos.Y - PlayerPos.Y,
			RenderLinePos.X - PlayerPos.X);

		float4 ToPlayer = Dis;
		ToPlayer.Size();

		std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		// 위에서 계산한 값에 맞춰 라인을 출력합니다.
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

void Boss::FSM_Boss_AirDashAttack()
{
	CreateStateParameter BossState_AirDashAttack_Param;

	BossState_AirDashAttack_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("Dash");
	};

	BossState_AirDashAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (false == GetGroundPixelCollision())
		{
			BossMainRenderer->ChangeAnimation("DashEnd");

			if (BossMainRenderer->IsCurAnimation("DashEnd")
				&& BossMainRenderer->IsCurAnimationEnd())
			{
				FSM_BossState.ChangeState(FSM_BossState::Idle);
				return;
			}
		}
		else
		{
			Transform.AddLocalPosition(float4::DOWN * _Delta * 600.0f);
		}
	};

	FSM_BossState.CreateState(FSM_BossState::AirDashAttack, BossState_AirDashAttack_Param);
}

void Boss::FSM_Boss_WallJump_Start()
{
	CreateStateParameter BossState_WallJumpStart_Param;

	BossState_WallJumpStart_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();

		Transform.SetLocalPosition({ 172.0f, -330.0f });

		BossMainRenderer->ChangeAnimation("WallIdle");
		BossMainRenderer->RightFlip();
	};

	BossState_WallJumpStart_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::WallJumpAttack);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::WallJumpAttack_Start, BossState_WallJumpStart_Param);
}

void Boss::FSM_Boss_WallJump()
{
	CreateStateParameter BossState_WallJump_Param;

	BossState_WallJump_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("WallJump");
	};

	BossState_WallJump_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

#pragma region 보스 점프 로직
		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		CheckPos = { Transform.GetWorldPosition() + RightCheck };
		MovePos = { (float4::RIGHT + float4::UP) * (Speed * 1.2f) * _Delta };

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
		{
			Transform.AddLocalPosition(MovePos);
		}

		if (false == GetGroundPixelCollision())
		{
			FSM_BossState.ChangeState(FSM_BossState::WallJumpAttack_End);
			return;
		}

#pragma endregion

		if (WallJumpTimer > 1.5f)
		{
			IsEndJumpAttack = true;
		}

		if (false == IsEndJumpAttack)
		{
			WallJumpTimer += _Delta;
		}

		if (WallJumpTimer > 0.8f && false == IsEndJumpAttack)
		{
			// 한번에 여러개 탄환을 생성하는 것을 테스트 할 때 사용
			//for (int i = 0; i < 15; i++)
			//{

			// 탄환을 새로 생성합니다.
			std::shared_ptr<BossBullet> BossNewBullet = GetLevel()->CreateActor<BossBullet>(static_cast<int>(ContentsRenderType::Play));

			// 탄환의 초기 위치를 설정합니다.
			BossNewBullet->Transform.SetLocalPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 60.0f });

			// 탄환이 이동할 방향을 계산합니다.
			float4 Direction = { -cosf(FireAngle * GameEngineMath::D2R), sinf(FireAngle * GameEngineMath::D2R) };

			// 계산된 방향으로 탄환이 이동하도록 변수 값을 설정해줍니다.
			BossNewBullet->MovePos = Direction;

			// 발사 각도를 설정한 간격값(AngleInterval)에 따라 증가하도록 합니다.
			FireAngle += AngleInterval;

			// 발사 각도가 언제나 0~360도를 유지하도록 보간합니다.
			if (FireAngle > 360)
			{
				FireAngle -= 360;
			}

			//}
			//IsEndJumpAttack = true;
			//WallJumpTimer = 0.0f;
		}

	};

	BossState_WallJump_Param.End = [=](class GameEngineState* _Parent)
	{
		IsEndJumpAttack = false;
		WallJumpTimer = 0.0f;

		// 시작 앵글값을 초기화합니다.
		FireAngle = 160;
	};

	FSM_BossState.CreateState(FSM_BossState::WallJumpAttack, BossState_WallJump_Param);
}

void Boss::FSM_Boss_WallJump_End()
{
	CreateStateParameter BossState_WallJumpEnd_Param;

	BossState_WallJumpEnd_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("WallLand");
	};

	BossState_WallJumpEnd_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::WallJumpAttack_End, BossState_WallJumpEnd_Param);
}

void Boss::FSM_Boss_GrenadeAttack_Start()
{
	CreateStateParameter BossState_GrenadeAttackStart_Param;

	BossState_GrenadeAttackStart_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("TakeOutGun");

	};

	BossState_GrenadeAttackStart_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::GrenadeAttack);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::GrenadeAttack_Start, BossState_GrenadeAttackStart_Param);
}

void Boss::FSM_Boss_GrenadeAttack()
{
	CreateStateParameter BossState_GrenadeAttack_Param;

	BossState_GrenadeAttack_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("Shoot");

		std::shared_ptr<BossGrenade> EnemyNewGrenade = GetLevel()->CreateActor<BossGrenade>(static_cast<int>(ContentsRenderType::Play));

		if (Dir == BossDir::Left)
		{
			EnemyNewGrenade->Transform.SetLocalPosition({ Transform.GetLocalPosition().X - 40.0f, Transform.GetLocalPosition().Y + 14.0f });
		}
		else
		{
			EnemyNewGrenade->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + 200.0f, Transform.GetLocalPosition().Y + 14.0f });
		}


	};

	BossState_GrenadeAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{


		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::GrenadeAttack_End);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::GrenadeAttack, BossState_GrenadeAttack_Param);
}

void Boss::FSM_Boss_GrenadeAttack_End()
{
	CreateStateParameter BossState_GrenadeAttackEnd_Param;

	BossState_GrenadeAttackEnd_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("PutBackGun");

	};

	BossState_GrenadeAttackEnd_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::GrenadeAttack_End, BossState_GrenadeAttackEnd_Param);
}

void Boss::FSM_Boss_WallTurretAttack()
{
	CreateStateParameter BossState_WallTurretAttack_Param;

	BossState_WallTurretAttack_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("Hurt");
	};

	BossState_WallTurretAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (FSM_BossState.GetStateTime() > 6.0f)
		{
			SetBossActivate();
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::WallTurretAttack, BossState_WallTurretAttack_Param);
}

void Boss::FSM_Boss_SuicideBombingAttack_Start()
{
	CreateStateParameter BossState_SuicideBombingAttackStart_Param;

	BossState_SuicideBombingAttackStart_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("RevealBomb");
	};

	BossState_SuicideBombingAttackStart_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::SuicideBombingAttack_Start, BossState_SuicideBombingAttackStart_Param);
}

void Boss::FSM_Boss_SuicideBombingAttack()
{
	CreateStateParameter BossState_SuicideBombingAttack_Param;

	BossState_SuicideBombingAttack_Param.Start = [=](class GameEngineState* _Parent)
	{
		BossMainRenderer->ChangeAnimation("RevealBomb");
	};

	BossState_SuicideBombingAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (BossMainRenderer->IsCurAnimationEnd())
		{
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::SuicideBombingAttack_Start, BossState_SuicideBombingAttack_Param);
}