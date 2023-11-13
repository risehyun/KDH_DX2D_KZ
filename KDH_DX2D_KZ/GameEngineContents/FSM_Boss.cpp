#include "PreCompile.h"
#include "Boss.h"

#include <GameEngineCore/GameEngineState.h>
#include "BossLaser.h"
#include "Player.h"
#include "BossBullet.h"
#include "BossGrenade.h"
#include "WallOpen.h"
#include "FX_Explosion.h"
#include "BossHead.h"
#include "Item_Knife.h"

void Boss::FSM_Boss_Idle()
{
	CreateStateParameter BossState_Idle_Param;

	BossState_Idle_Param.Start = [=](class GameEngineState* _Parent)
	{
		BasePatternTimer = 0.0f;
		BossMainRenderer->ChangeAnimation("Idle");
	};

	BossState_Idle_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// Idle 상태인 동안에는 중력이 작용합니다.
		Gravity(_Delta);

		BasePatternTimer += _Delta;

		if (BasePatternTimer > 1.0f && true == IsUsingAutoPattern)
		{
			GameEngineRandom Random;

			// 패턴 랜덤 선택
			int Count = Random.RandomInt(0, 4);
			switch (Count)
			{
			case 0:
				FSM_BossState.ChangeState(FSM_BossState::GroundRifleAttack_Start);
				break;

			case 1:
				FSM_BossState.ChangeState(FSM_BossState::GrenadeAttack_Start);
				break;

			case 2:
				FSM_BossState.ChangeState(FSM_BossState::GroundDashAttack);
				break;

			case 3:
				FSM_BossState.ChangeState(FSM_BossState::WallJumpAttack_Start);
				break;

			case 4:
				FSM_BossState.ChangeState(FSM_BossState::AirRifleAttack_Start);
				break;

			default:
				break;
			}
		}

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

		if (GameEngineInput::IsDown('0', this))
		{
			FSM_BossState.ChangeState(FSM_BossState::DodgeRoll);
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

		float4 PlayerPos = Player::MainPlayer->Transform.GetLocalPosition();
		Dis = PlayerPos - Transform.GetLocalPosition();

		// 라인 범위 계산
		float4 RenderLinePos = Transform.GetLocalPosition();

		float4 angle = atan2(RenderLinePos.Y - PlayerPos.Y,
			RenderLinePos.X - PlayerPos.X);

		//		OutputDebugStringA(std::to_string(angle.X * GameEngineMath::R2D).c_str());

		float t = abs(angle.X * GameEngineMath::R2D);
		float4 LaserFirePos = float4::ZERO;

		if (t >= 180.0f && t < 190.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_180");
			LaserFirePos = { Transform.GetLocalPosition().X + 40.0f, Transform.GetLocalPosition().Y + 14.0f };
		}

		if (t >= 170.0f && t < 180.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_180");
			LaserFirePos = { Transform.GetLocalPosition().X + 40.0f, Transform.GetLocalPosition().Y + 14.0f };
		}

		if (t >= 160.0f && t < 170.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_160");
			LaserFirePos = { Transform.GetLocalPosition().X + 35.0f, Transform.GetLocalPosition().Y + 22.0f };
		}

		if (t >= 150.0f && t < 160.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_150");
			LaserFirePos = { Transform.GetLocalPosition().X + 30.0f, Transform.GetLocalPosition().Y + 30.0f };
		}

		if (t >= 140.0f && t < 150.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_140");
			LaserFirePos = { Transform.GetLocalPosition().X + 25.0f, Transform.GetLocalPosition().Y + 30.0f };
		}

		if (t >= 130.0f && t < 140.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_130");
			LaserFirePos = { Transform.GetLocalPosition().X + 20.0f, Transform.GetLocalPosition().Y + 30.0f };
		}

		if (t >= 120.0f && t < 130.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_120");
			LaserFirePos = { Transform.GetLocalPosition().X + 15.0f, Transform.GetLocalPosition().Y + 34.0f };
		}

		if (t >= 110.0f && t < 120.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_110");
			LaserFirePos = { Transform.GetLocalPosition().X + 10.0f, Transform.GetLocalPosition().Y + 42.0f };
		}

		if (t >= 100.0f && t < 110.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_100");
			LaserFirePos = { Transform.GetLocalPosition().X + 8.0f, Transform.GetLocalPosition().Y + 50.0f };
		}

		if (t >= 90.0f && t < 100.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_90");
			LaserFirePos = { Transform.GetLocalPosition().X + 2.0f, Transform.GetLocalPosition().Y + 58.0f };
		}

		if (t >= 80.0f && t < 90.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_100");
			LaserFirePos = { Transform.GetLocalPosition().X - 8.0f, Transform.GetLocalPosition().Y + 50.0f };
		}

		if (t >= 70.0f && t < 80.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_110");
			LaserFirePos = { Transform.GetLocalPosition().X - 10.0f, Transform.GetLocalPosition().Y + 42.0f };
		}

		if (t >= 60.0f && t < 70.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_120");
			LaserFirePos = { Transform.GetLocalPosition().X - 15.0f, Transform.GetLocalPosition().Y + 34.0f };
		}

		if (t >= 50.0f && t < 60.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_130");
			LaserFirePos = { Transform.GetLocalPosition().X - 20.0f, Transform.GetLocalPosition().Y + 30.0f };
		}

		if (t >= 40.0f && t < 50.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_140");
			LaserFirePos = { Transform.GetLocalPosition().X - 25.0f, Transform.GetLocalPosition().Y + 30.0f };
		}

		if (t >= 30.0f && t < 40.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_150");
			LaserFirePos = { Transform.GetLocalPosition().X - 30.0f, Transform.GetLocalPosition().Y + 30.0f };
		}

		if (t >= 20.0f && t < 30.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_160");
			LaserFirePos = { Transform.GetLocalPosition().X - 35.0f, Transform.GetLocalPosition().Y + 22.0f };
		}

		if (t >= 10.0f && t < 20.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_170");
			LaserFirePos = { Transform.GetLocalPosition().X - 40.0f, Transform.GetLocalPosition().Y + 14.0f };
		}

		if (t >= 0.0f && t < 10.0f)
		{
			BossMainRenderer->ChangeAnimation("AimRifle_180");
			LaserFirePos = { Transform.GetLocalPosition().X - 40.0f, Transform.GetLocalPosition().Y + 14.0f };
		}

		FxPlayer = GameEngineSound::SoundPlay("sound_boss_lasershot.wav");

		std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));

		// 위에서 계산한 값에 맞춰 라인을 출력합니다.
		if (Dir == BossDir::Left)
		{
			BossNewLaser->InitBossLaserData(BossLaserType::Normal, float4::LEFT, LaserFirePos, float4::ZERO);
			BossNewLaser->BossLaserRenderer->LeftFlip();
		}
		else
		{
			BossNewLaser->InitBossLaserData(BossLaserType::Normal, float4::RIGHT, LaserFirePos, float4::ZERO);
			BossNewLaser->BossLaserRenderer->LeftFlip();
		}

		BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		BossNewLaser->BossLaserRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });
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
		FxPlayer = GameEngineSound::SoundPlay("sound_boss_lasershot_swipe.wav");

		BossMainRenderer->RightFlip();

		GameEngineRandom Random;

		// 이동 위치 랜덤 설정

		if (GetBossHp() != 1)
		{
			AirRifleAttackCount = Random.RandomInt(0, 2);
		}

		switch (AirRifleAttackCount)
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
			if (1 == GetBossHp())
			{
				if (AirRifleAttackCount != 2)
				{
					AirRifleAttackCount = 2;
					FSM_BossState.ChangeState(FSM_BossState::AirRifleAttack_Start);
					return;
				}
				else
				{
					FSM_BossState.ChangeState(FSM_BossState::WallJumpAttack_Start);
					return;
				}
			}

			if (0 == AirRifleAttackCount)
			{
				FSM_BossState.ChangeState(FSM_BossState::AirDashAttack);
				return;
			}
		
			if (true == GetGroundPixelCollision())
			{
				FSM_BossState.ChangeState(FSM_BossState::Fall);
				return;
			}
			else
			{
				FSM_BossState.ChangeState(FSM_BossState::Idle);
				return;
			}
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

		FxPlayer = GameEngineSound::SoundPlay("sound_boss_lasershot_vertical.wav");

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

			FxPlayer = GameEngineSound::SoundPlay("sound_boss_lasershot_vertical.wav");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.0f && FSM_BossState.GetStateTime() < 1.1f)
		{
			Transform.SetLocalPosition({ 330, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn", true);

			FxPlayer = GameEngineSound::SoundPlay("sound_boss_lasershot_vertical.wav");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 1.5f && FSM_BossState.GetStateTime() < 1.6f)
		{
			Transform.SetLocalPosition({ 940, -180 });
			BossMainRenderer->ChangeAnimation("TeleportIn", true);

			FxPlayer = GameEngineSound::SoundPlay("sound_boss_lasershot_vertical.wav");

			std::shared_ptr<BossLaser> BossNewLaser = GetLevel()->CreateActor<BossLaser>(static_cast<int>(ContentsRenderType::Play));
			BossNewLaser->InitBossLaserData(BossLaserType::Vertical, float4::LEFT, { Transform.GetLocalPosition().X, Transform.GetLocalPosition().Y - 20.0f }, float4::ZERO);
			BossNewLaser->BossLaserRenderer->SetPivotType(PivotType::Right);
		}

		if (FSM_BossState.GetStateTime() > 2.0f)
		{
			BossMainRenderer->ChangeAnimation("TeleportOut");

			if (BossMainRenderer->IsCurAnimationEnd())
			{

				if (1 == GetBossHp())
				{
					FSM_BossState.ChangeState(FSM_BossState::AirRifleAttack_Start);
					return;
				}

				if (true == GetGroundPixelCollision())
				{
					FSM_BossState.ChangeState(FSM_BossState::Fall);
					return;
				}
				else
				{
					FSM_BossState.ChangeState(FSM_BossState::Idle);
					return;
				}
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
			if (true == GetGroundPixelCollision())
			{
				FSM_BossState.ChangeState(FSM_BossState::Fall);
				return;
			}
			else
			{
				FSM_BossState.ChangeState(FSM_BossState::WallJumpAttack_Start);
				return;
			}

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

		if (Dir == BossDir::Left)
		{
			Transform.SetLocalPosition({ 172.0f, -330.0f });
			BossMainRenderer->RightFlip();
		}

		else
		{
			Transform.SetLocalPosition({ 1128.0f, -330.0f });
			BossMainRenderer->LeftFlip();
		}

		BossMainRenderer->ChangeAnimation("WallIdle");

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
		FxPlayer = GameEngineSound::SoundPlay("sound_boss_gatling.wav");
		BossMainRenderer->ChangeAnimation("WallJump");
	};

	BossState_WallJump_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

#pragma region 보스 점프 로직
		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		if (Dir == BossDir::Left)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = { (float4::RIGHT + float4::UP) * (Speed * 1.2f) * _Delta };
		}
		else
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = { (float4::LEFT + float4::UP) * (Speed * 1.2f) * _Delta };
		}

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
		FxPlayer = GameEngineSound::SoundPlay("sound_gun_fire.wav");

		std::shared_ptr<BossGrenade> EnemyNewGrenade = GetLevel()->CreateActor<BossGrenade>(static_cast<int>(ContentsRenderType::Play));

		if (0 == GrenadeAttackCount)
		{
			DirCheck();

			BossMainRenderer->ChangeAnimation("Shoot", true);
			EnemyNewGrenade->SetGrenadeSpeed(10.0f);
		}

		if (1 == GrenadeAttackCount)
		{
			BossMainRenderer->ChangeAnimation("Shoot", true);
			EnemyNewGrenade->SetGrenadeSpeed(30.0f);
		}

		if (2 == GrenadeAttackCount)
		{
			BossMainRenderer->ChangeAnimation("Shoot", true);
			EnemyNewGrenade->SetGrenadeSpeed(60.0f);
		}

		if (Dir == BossDir::Left)
		{
			EnemyNewGrenade->Transform.SetLocalPosition({ Transform.GetLocalPosition().X - 40.0f, Transform.GetLocalPosition().Y + 14.0f });
			EnemyNewGrenade->SetGrenadeDir(float4::LEFT);
		}
		else
		{
			EnemyNewGrenade->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + 40.0f, Transform.GetLocalPosition().Y + 14.0f });
			EnemyNewGrenade->SetGrenadeDir(float4::RIGHT);
		}

	};

	BossState_GrenadeAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (BossMainRenderer->IsCurAnimationEnd() && GrenadeAttackCount == 0)
		{
			++GrenadeAttackCount;
			FSM_BossState.ChangeState(FSM_BossState::GrenadeAttack);

			return;
		}


		if (BossMainRenderer->IsCurAnimationEnd() && GrenadeAttackCount == 1)
		{
			++GrenadeAttackCount;
			FSM_BossState.ChangeState(FSM_BossState::GrenadeAttack);
			return;
		}

		if (BossMainRenderer->IsCurAnimationEnd() && GrenadeAttackCount == 2)
		{
			FSM_BossState.ChangeState(FSM_BossState::GrenadeAttack_End);
			GrenadeAttackCount = 0;
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
			FSM_BossState.ChangeState(FSM_BossState::SuicideBombingAttack);
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
		DirCheck();
		PreDir = Dir;
		BossMainRenderer->ChangeAnimation("BombRun");
	};

	BossState_SuicideBombingAttack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		DirCheck();

		if (Dir != PreDir)
		{

			GameEngineRandom Random;

			// FX 생성 위치 랜덤 설정
			for (int i = 0; i < 50; i++)
			{
				int RandomPosX = Random.RandomInt(-110, 110);
				int RandomPosY = Random.RandomInt(-80, 80);

				std::shared_ptr<FX_Explosion> EnemyNewBullet = GetLevel()->CreateActor<FX_Explosion>(static_cast<int>(ContentsRenderType::Play));
				EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + RandomPosX, Transform.GetLocalPosition().Y + RandomPosY });
			}

			FSM_BossState.ChangeState(FSM_BossState::DieLand);
			return;
		}


		if (Dir == BossDir::Left)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = { float4::LEFT * Speed * _Delta };
		}
		else
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = { float4::RIGHT * Speed * _Delta };
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(MovePos);
		}
		else
		{

			GameEngineRandom Random;

			// FX 생성 위치 랜덤 설정
			for (int i = 0; i < 50; i++)
			{
				int RandomPosX = Random.RandomInt(-110, 110);
				int RandomPosY = Random.RandomInt(-80, 80);

				std::shared_ptr<FX_Explosion> EnemyNewBullet = GetLevel()->CreateActor<FX_Explosion>(static_cast<int>(ContentsRenderType::Play));
				EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + RandomPosX, Transform.GetLocalPosition().Y + RandomPosY });
			}

			FSM_BossState.ChangeState(FSM_BossState::DieLand);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::SuicideBombingAttack, BossState_SuicideBombingAttack_Param);
}

void Boss::FSM_Boss_DodgeRoll()
{
	CreateStateParameter BossState_DodgeRoll_Param;

	BossState_DodgeRoll_Param.Start = [=](class GameEngineState* _Parent)
	{

		DirCheck();

		BossMainRenderer->ChangeAnimation("DodgeRoll");

		if (nullptr != BossMainCollision)
		{
			BossMainCollision->Off();
		}

	};

	BossState_DodgeRoll_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		Speed = 500.0f;

		if (Dir == BossDir::Left)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = { float4::LEFT * _Delta * Speed };
		}

		else if (Dir == BossDir::Right)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = { float4::RIGHT * _Delta * Speed };
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddWorldPosition(MovePos);
		}

		// 구르기 모션이 끝나면
		if (GetMainRenderer()->IsCurAnimationEnd())
		{
			// 속도를 원래대로 낮춰줍니다.
			Speed = 300.0f;

			// Idle 상태로 전환합니다.

			if (nullptr != BossMainCollision)
			{
				BossMainCollision->On();
			}

			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}

	};

	FSM_BossState.CreateState(FSM_BossState::DodgeRoll, BossState_DodgeRoll_Param);
}

void Boss::FSM_Boss_Hurt()
{
	CreateStateParameter BossState_Hurt_Param;

	BossState_Hurt_Param.Start = [=](class GameEngineState* _Parent)
	{
		if (-1 != GetBossHp())
		{
			FxPlayer = GameEngineSound::SoundPlay("sound_boss_hurt1.wav");
			DirCheck();
			BossMainRenderer->ChangeAnimation("Hurt");
			Speed = 600.0f;
		}

	};

	BossState_Hurt_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (-1 == GetBossHp())
		{
			FSM_BossState.ChangeState(FSM_BossState::Death);
			return;
		}

		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		if (Dir == BossDir::Left)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = { (float4::RIGHT)*_Delta * Speed };
		}

		else if (Dir == BossDir::Right)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = { (float4::LEFT)*_Delta * Speed };
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE && FSM_BossState.GetStateTime() < 0.4f)
		{
			Transform.AddWorldPosition(MovePos);
		}

		if (GetMainRenderer()->IsCurAnimationEnd())
		{
			Speed = 200.0f;

			if (2 == GetBossHp())
			{
				SetBossDeactivate();
				FSM_BossState.ChangeState(FSM_BossState::WallTurretAttack);
				return;
			}

			if (1 == GetBossHp())
			{
				FSM_BossState.ChangeState(FSM_BossState::MultipleAirRifleAttack_Start);
				return;
			}

			if (0 == GetBossHp())
			{
				FSM_BossState.ChangeState(FSM_BossState::SuicideBombingAttack_Start);
				return;
			}

		}

	};

	FSM_BossState.CreateState(FSM_BossState::Hurt, BossState_Hurt_Param);

}

void Boss::FSM_Boss_Fall()
{
	CreateStateParameter BossState_Fall_Param;

	BossState_Fall_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("Fall");
		Speed = 600.0f;
	};

	BossState_Fall_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		Gravity(_Delta);

		if (false == GetGroundPixelCollision())
		{
			Speed = 200.0f;
			FSM_BossState.ChangeState(FSM_BossState::Idle);
			return;
		}

	};

	FSM_BossState.CreateState(FSM_BossState::Fall, BossState_Fall_Param);

}

void Boss::FSM_Boss_DieLand()
{
	CreateStateParameter BossState_DieLand_Param;

	BossState_DieLand_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("DieLand");
		Speed = 600.0f;
	};

	BossState_DieLand_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		if (FSM_BossState.GetStateTime() < 1.0f)
		{
			if (Dir == BossDir::Left)
			{
				CheckPos = { Transform.GetWorldPosition() + LeftCheck };
				MovePos = { (float4::LEFT) };
			}

			else if (Dir == BossDir::Right)
			{
				CheckPos = { Transform.GetWorldPosition() + RightCheck };
				MovePos = { (float4::RIGHT) };
			}

			GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

			if (Color != GameEngineColor::WHITE)
			{
				// ★ 글로벌 변수로 바꿔서 쓰기 
				// 벽 오른쪽
				if (1128.0f < Transform.GetLocalPosition().X)
				{
					MovePos = { (float4::LEFT + float4::DOWN) * 0.3f };
				}

				// 벽 왼쪽
				else if (160.0f > Transform.GetLocalPosition().X)
				{
					MovePos = { (float4::RIGHT + float4::DOWN) * 0.3f };
				}
			}

			Transform.AddWorldPosition(MovePos * _Delta * Speed);
		}

		else
		{
			FSM_BossState.ChangeState(FSM_BossState::Crawl);
			return;
		}
	};

	FSM_BossState.CreateState(FSM_BossState::DieLand, BossState_DieLand_Param);

}

void Boss::FSM_Boss_Crawl()
{
	CreateStateParameter BossState_Crawl_Param;

	BossState_Crawl_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		Speed = 3.0f;
		BossMainRenderer->ChangeAnimation("Crawl");
	};

	BossState_Crawl_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		if (Dir == BossDir::Left)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = { (float4::LEFT) };
		}

		else if (Dir == BossDir::Right)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = { (float4::RIGHT) };
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddWorldPosition(MovePos * _Delta * Speed);
		}

	};

	FSM_BossState.CreateState(FSM_BossState::Crawl, BossState_Crawl_Param);

}

void Boss::FSM_Boss_Death()
{
	CreateStateParameter BossState_Death_Param;

	BossState_Death_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();
		BossMainRenderer->ChangeAnimation("Death");

		std::shared_ptr<BossHead> NewBossHead = GetLevel()->CreateActor<BossHead>(static_cast<int>(ContentsRenderType::Play));
		NewBossHead->Transform.SetWorldPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y + 100.0f });
		NewBossHead->SetMapTexture("Map_BossLevel1_2.png");

		if (Dir == BossDir::Left)
		{
			NewBossHead->SetDir(float4::RIGHT);
		}

		else if (Dir == BossDir::Right)
		{
			NewBossHead->SetDir(float4::LEFT);
		}

	};

	BossState_Death_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

	};

	FSM_BossState.CreateState(FSM_BossState::Death, BossState_Death_Param);

}