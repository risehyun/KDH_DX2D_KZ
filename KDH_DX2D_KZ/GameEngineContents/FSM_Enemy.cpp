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

		else if (Type != EnemyType::WallTurret)
		{
			// Idle ������ ���ȿ��� �߷��� �ۿ��մϴ�.
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

	//	OutputDebugStringA(PlayerChasePos.ToString("\n").c_str());

		//// ���鿡 �ִ� ���
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
		if (PlayerChasePos.X > 600.0f && Type != EnemyType::WallTurret)
		{
			// ��� ���·� �����մϴ�.
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

		// ���� ���¿����� ���̻� �浹 �ۿ��� �Ͼ�� �ʵ��� �浹ü�� ���ݴϴ�.
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
			// ���� Enemy�� ���� üũ(�ͷ��� ��� ���� ��ȯ�� ���� �����Ƿ� ����)
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
		else // ���Ÿ� ������ �ϴ� Enemy�� ���
		{
			EnemyEffectRenderer->ChangeAnimation("GunSpark", true);
			EnemyEffectRenderer->On();

			AttackFireInitPos = { Transform.GetWorldPosition().X - 70.0f, Transform.GetWorldPosition().Y + 10.0f };
			EnemyEffectRenderer->Transform.SetLocalPosition({ -70.0f, 10.0f });
			AttackFireDir = float4::LEFT;
		}


		EnemyMainRenderer->ChangeAnimation("Attack", true);
	

		// �ٰŸ� Enemy�� �ƴ� ���
		if (Type != EnemyType::ShieldCop)
		{
			EffectPlayer = GameEngineSound::SoundPlay("sound_gun_fire.wav");
			// Bullet ����
			std::shared_ptr<Bullet> EnemyNewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(ContentsRenderType::Play));
	
			// ���� ���� ���
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

		// ���� ���� ���� ���� �޾� Death ó�� �Ǹ� �Ʒ� ������ �������� �ʰ� �ٷ� Death ���·� ��ȯ�մϴ�.
		if (true == IsEnemyDeath)
		{
			FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
			return;
		}

		if (Type != EnemyType::WallTurret)
		{
			// WallTurret�� ���� ������ �����̹Ƿ� �߷� ������ ���� �ʽ��ϴ�.
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