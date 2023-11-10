#include "PreCompile.h"
#include <GameEngineCore/GameEngineState.h>

#include "Player.h"
#include "UI_Mouse.h"
#include "GameStateManager.h"
#include "PlayerAttack.h"

void Player::FSM_Player_Idle()
{
	CreateStateParameter PlayerState_Idle_Param;

	PlayerState_Idle_Param.Start = [=](class GameEngineState* _Parent)
	{
		MainSpriteRenderer->ChangeAnimation("Idle");
	};

	PlayerState_Idle_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// Idle ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);
		DirCheck();

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// <���� ���� Ű�� ������ ��>
		// ���� ���� Ű�� ������ Jump ���¿� �����մϴ�.
		if (GameEngineInput::IsDown('W', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Jump);
			return;
		}

		// <�Ʒ��� ���� Ű�� ������ ��>
		// �Ʒ� Ű�� ������ ������ PreCrouch ���¿� �����ϰų�,
		// �ٷ� �Ʒ��� �ȼ��� �˻��� ������ Ǫ������ ��쿡�� Fall ���·� �����մϴ�.
		if (GameEngineInput::IsDown('S', this))
		{
			CheckPos = { Transform.GetWorldPosition() + DownCheck };
			MovePos = { 0.0f, -Speed * _Delta };

			GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

			if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
			{
				Transform.AddLocalPosition(MovePos);
				FSM_PlayerState.ChangeState(FSM_PlayerState::Fall);
				return;
			}

			// ����� �Ͼ���� �ƴϰ�, �Ʒ��� �̵��� ������ �Ķ����� �ƴ϶�� (�⺻������ ������ ��)
			else
			{
				// ���̱Ⱑ �⺻�̰�, ������� ��ȯ�� ���������� PreCrouch ���·� ��ȯ�ϰ� �����մϴ�.
				FSM_PlayerState.ChangeState(FSM_PlayerState::PreCrouch);
				return;
			}
		}

		// ���� Ȥ�� ������ �̵� ��ư�� ������ �̵�(Run) ���·� ��ȯ�ϰ� �����մϴ�.
		if (GameEngineInput::IsDown('A', this) || GameEngineInput::IsDown('D', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Run);
			return;
		}

		// ������ ���콺 ��ư�� ������ �뽬 ���·� ��ȯ�ϰ� �����մϴ�.
		if (GameEngineInput::IsDown(VK_RBUTTON, this)
			&& CurPlayerDashCoolTime <= 0.0f
			&& GameStateManager::GameState->GetCurTimeControlBattery() >= 0)
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Dash);
			return;
		}

		// ���� ���콺 ��ư�� ������ ���� ���·� ��ȯ�ϰ� �����մϴ�.
		if (GameEngineInput::IsDown(VK_LBUTTON, this)
			&& CurPlayerDashCoolTime <= 0.0f)
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Attack);
			return;
		}


	};

	FSM_PlayerState.CreateState(FSM_PlayerState::Idle, PlayerState_Idle_Param);

}

void Player::FSM_Player_Jump()
{
	CreateStateParameter PlayerState_Jump_Param;

	PlayerState_Jump_Param.Start = [=](class GameEngineState* _Parent)
	{
		MainSpriteRenderer->ChangeAnimation("Jump");
	};

	PlayerState_Jump_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{

		if (GameEngineInput::IsDown(VK_LBUTTON, this)
			&& CurPlayerDashCoolTime <= 0.0f)
		{
			PlayerFXRenderer->Off();
			FSM_PlayerState.ChangeState(FSM_PlayerState::Attack);
			return;
		}


		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		CheckPos = { Transform.GetWorldPosition() + UpCheck };
		MovePos = { 0.0f, float4::UP.Y * Speed * _Delta };

		if (GameEngineInput::IsPress('D', this))
		{
			DirCheck();
			CheckPos = { Transform.GetWorldPosition() + RightCheck + UpCheck };
			MovePos = { (float4::RIGHT + float4::UP) * Speed * _Delta };
		}

		else if (GameEngineInput::IsPress('A', this))
		{
			DirCheck();
			CheckPos = { Transform.GetWorldPosition() + LeftCheck + UpCheck };
			MovePos = { (float4::LEFT + float4::UP) * Speed * _Delta };
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
		{
			Transform.AddLocalPosition(MovePos);
		}

		else
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Fall);
			return;
		}

		// ���� �׽�Ʈ ���� -100.0f
		if (GetGravityVector().Y <= -200.0f)
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Fall);
			return;
		}

	};

	FSM_PlayerState.CreateState(FSM_PlayerState::Jump, PlayerState_Jump_Param);
}

void Player::FSM_Player_PreCrouch()
{
	CreateStateParameter PlayerState_PreCrouch_Param;

	PlayerState_PreCrouch_Param.Start = [=](class GameEngineState* _Parent)
	{
		MainSpriteRenderer->ChangeAnimation("PreCrouch");
	};

	PlayerState_PreCrouch_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// PreCrouch ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);
		DirCheck();

		// PreCrouch ���¿��� ������ ���� ����Ű�� ������ ������(Roll) ���·� ��ȯ�մϴ�.
		if (GameEngineInput::IsDown('D', this) || GameEngineInput::IsDown('A', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Roll);
			return;
		}

		// Ű�� ���� Idle ���·� ����
		if (GameEngineInput::IsFree('S', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
			return;
		}


	};

	FSM_PlayerState.CreateState(FSM_PlayerState::PreCrouch, PlayerState_PreCrouch_Param);
}

// �� �����⸦ �� �� Dust �߻�
void Player::FSM_Player_Roll()
{
	CreateStateParameter PlayerState_Roll_Param;

	PlayerState_Roll_Param.Start = [=](class GameEngineState* _Parent)
	{
		MainSpriteRenderer->ChangeAnimation("Roll");
		PlayerBodyCollision->Off();
	};

	PlayerState_Roll_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// PreCrouch ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);
		DirCheck();

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// �����⸦ �ϴ� ���� �ӵ��� ��Һ��� �ణ �� �������ϴ�. �⺻�� : 300
		// �� ������ ����� �Ҵ����� ���� ���� �����ؼ� �Ҵ��� ��
		Speed = 500.0f;

		if (float4::LEFT == Player::MainPlayer->GetPlayerDir())
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = { float4::LEFT * _Delta * Speed };
		}

		else if (float4::RIGHT == Player::MainPlayer->GetPlayerDir())
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = { float4::RIGHT * _Delta * Speed };
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddWorldPosition(MovePos);
		}

		// ������ ����� ������
		if (GetMainRenderer()->IsCurAnimationEnd())
		{
			// �ӵ��� ������� �����ݴϴ�.
			Speed = 300.0f;

			// Idle ���·� ��ȯ�մϴ�.
			PlayerBodyCollision->On();
			FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
			return;
		}

	};

	FSM_PlayerState.CreateState(FSM_PlayerState::Roll, PlayerState_Roll_Param);
}

void Player::FSM_Player_Fall()
{
	CreateStateParameter PlayerState_Fall_Param;

	PlayerState_Fall_Param.Start = [=](class GameEngineState* _Parent)
	{
		MainSpriteRenderer->ChangeAnimation("Fall");
	};

	PlayerState_Fall_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// PreCrouch ������ ���ȿ��� �߷��� �ۿ��մϴ�.
		Gravity(_Delta);
		DirCheck();

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// ���� ���콺 ��ư�� ������ ���� ���·� ��ȯ�ϰ� �����մϴ�.
		if (GameEngineInput::IsDown(VK_LBUTTON, this)
			&& CurPlayerDashCoolTime <= 0.0f)
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Attack);
			return;
		}

		if (GameEngineInput::IsPress('D', this))
		{
			DirCheck();
			CheckPos = { Transform.GetWorldPosition() + RightCheck + DownCheck };
			MovePos = { (float4::RIGHT + float4::DOWN) * 200.0f * _Delta };

			//			SetGravityVector((float4::DOWN + float4::RIGHT) * 200.0f);
		}

		else if (GameEngineInput::IsPress('A', this))
		{
			DirCheck();
			CheckPos = { Transform.GetWorldPosition() + LeftCheck + DownCheck };
			MovePos = { (float4::LEFT + float4::DOWN) * 200.0f * _Delta };
			//			SetGravityVector((float4::DOWN + float4::LEFT) * 200.0f.0f);
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color != GameEngineColor::RED)
		{
			Transform.AddLocalPosition(MovePos);
		}


		if (false == GetGroundPixelCollision())
		{
			PlayerFXRenderer->ChangeAnimation("LandCloud");
			PlayerFXRenderer->Transform.SetLocalPosition({ 0.0f, -24.0f, 0.0f, 1.0f });
			PlayerFXRenderer->On();

			FxPlayer = GameEngineSound::SoundPlay("sound_player_land.wav");

			if (true == PlayerFXRenderer->IsCurAnimationEnd())
			{

				PlayerFXRenderer->Off();
			}

			FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
			//FSM_PlayerState.ChangeState(FSM_PlayerState::PostCrouch);
			return;
		}

	};

	FSM_PlayerState.CreateState(FSM_PlayerState::Fall, PlayerState_Fall_Param);
}

void Player::FSM_Player_Run()
{
	CreateStateParameter PlayerState_Run_Param;

	PlayerState_Run_Param.Start = [=](class GameEngineState* _Parent)
	{
		FxPlayer = GameEngineSound::SoundPlay("sound_player_running_1.wav");
		MainSpriteRenderer->ChangeAnimation("Run");
	};

	PlayerState_Run_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		Gravity(_Delta);

		DirCheck();

		//if (true == GetGroundPixelCollision())
		//{
		//	PlayerFXRenderer->Off();
		//	ChangeState(PlayerState::Fall);
		//	return;
		//}

		if (GameEngineInput::IsPress('W', this))
		{
			DirCheck();
			FSM_PlayerState.ChangeState(FSM_PlayerState::Jump);
			return;
		}

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		PlayerFXRenderer->On();
		PlayerFXRenderer->ChangeAnimation("RunCloud");

		if (GameEngineInput::IsPress('A', this))
		{
			Gravity(_Delta);
			DirCheck();
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = { float4::LEFT * _Delta * Speed };
		}

		if (GameEngineInput::IsPress('D', this))
		{
			Gravity(_Delta);
			DirCheck();
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = { float4::RIGHT * _Delta * Speed };
		}

		if (GameEngineInput::IsPress('S', this))
		{
			DirCheck();
			CheckPos = { Transform.GetWorldPosition() + DownCheck };

			GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

			if (Color == GameEngineColor::RED)
			{
				FSM_PlayerState.ChangeState(FSM_PlayerState::PreCrouch);
				return;
			}

			MovePos = { float4::DOWN * Speed * _Delta };
		}

		if (GameEngineInput::IsDown(VK_LBUTTON, this)
			&& CurPlayerDashCoolTime <= 0.0f)
		{
			PlayerFXRenderer->Off();
			FSM_PlayerState.ChangeState(FSM_PlayerState::Attack);
			return;
		}

		// �� �̻� �Է��� ������ ���� ������ �����ϰ� Idle ���·� ��ȯ �� �����մϴ�.
		if (MovePos == float4::ZERO)
		{
			DirCheck();
			PlayerFXRenderer->Off();
			FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
			return;
		}



		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);


		if (Color == GameEngineColor::WHITE || Color == GameEngineColor::BLUE)
		{
			Transform.AddWorldPosition(MovePos);
		}




	};

	FSM_PlayerState.CreateState(FSM_PlayerState::Run, PlayerState_Run_Param);


}

void Player::FSM_Player_Dash()
{
	CreateStateParameter PlayerState_Dash_Param;

	PlayerState_Dash_Param.Start = [=](class GameEngineState* _Parent)
	{
		IsOnDash = true;
		PlayerRenderer_Dash->On();
		//	IsOnDashCoolTimeDecrease = false;

			// �뽬 ������ ��Ȱ�� ���¸� Ȱ��ȭ�Ͽ� ȭ�鿡 ���̵��� �մϴ�.
		if (false == PlayerRenderer_DashLine->GetUpdateValue())
		{
			PlayerRenderer_DashLine->On();
		}
	};

	PlayerState_Dash_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// Dash ������ ���� �߷�, ���� ������ �ۿ��մϴ�.
		Gravity(_Delta);
		DirCheck();

		if (GameStateManager::GameState->GetCurTimeControlBattery() < 0)
		{
			// �� Reset Dash State ���� �Լ��� ���� ���� ���
			IsOnDash = false;

			if (true == PlayerRenderer_DashLine->GetUpdateValue())
			{
				PlayerRenderer_DashLine->Off();
			}

			if (true == PlayerRenderer_Dash->GetUpdateValue())
			{
				PlayerRenderer_Dash->Off();
			}

			FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
			return;
		}

		// ��ġ ����� ���� ���� �� ����
		float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
		MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();

		// Ŭ���� ��ġ�� ����մϴ�.
		float4 PlayerNextPos = UI_Mouse::Mouse->GetMouseWorldToActorPos() - PlayerPos;

		// ���� ���� ���
		float4 RenderLinePos = Transform.GetWorldPosition();

		float4 angle = atan2(MousePos.Y - RenderLinePos.Y,
			MousePos.X - RenderLinePos.X);

		// ����׿�
		// OutputDebugStringA(angle.ToString("\n").c_str());

		ToMouse = MousePos - RenderLinePos;
		ToMouse.Size();

		//	�̵� ������ max range, min range�� ����� �ʵ��� �����մϴ�.
		if (ToMouse.X > 440.0f)
		{
			ToMouse.X = 440.0f;
		}

		if (ToMouse.X < -440.0f)
		{
			ToMouse.X = -440.0f;
		}

		else if (ToMouse.Y > 440.0f)
		{
			ToMouse.Y = 440.0f;
		}

		if (ToMouse.Y < -440.0f)
		{
			ToMouse.Y = -440.0f;
		}

		// ������ ����� ���� ���� ������ ����մϴ�.
		PlayerRenderer_DashLine->SetPivotType(PivotType::Left);
		PlayerRenderer_DashLine->Transform.SetWorldScale({ ToMouse.Size() / 4.0f , 2.0f, 1.0f });
		PlayerRenderer_DashLine->Transform.SetWorldRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });
		PlayerRenderer_DashLine->Transform.SetWorldPosition(PlayerPos);

		PlayerDashCollision->Transform.SetWorldScale({ ToMouse.Size(), 2.0f, 1.0f });
		PlayerDashCollision->Transform.SetWorldRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });
		PlayerDashCollision->Transform.SetWorldPosition(PlayerPos);

		//PlayerRenderer_DashLine->Transform.SetLocalScale({ 20.0f, 20.0f, 1.0f });
		//PlayerRenderer_DashLine->Transform.SetWorldPosition(Transform.GetWorldPosition());


		// ��ư�� ���� �ִ� ���� �̵� ������ ��ȿ���� Ȯ���� ��,
		// �ռ� ���� ��ġ�� �÷��̾ �̵��մϴ�.
		if (true == GameEngineInput::IsFree(VK_RBUTTON, this))
		{

			while (true == Player::MainPlayer->IsOnDash)
			{
				GameEngineColor ColorCheck =
					Player::MainPlayer->GetMapColor(PlayerNextPos, GameEngineColor::WHITE);

				//  ����׿�
				//	UI_Mouse::Mouse->MouseCollision->Transform.SetLocalPosition(PlayerNextPos);

					// �̵��� ���� ��ȿ ������ �ƴ� ��� Dash ���¸� ����մϴ�.
				if (ColorCheck != GameEngineColor::WHITE)
				{
					IsOnDash = false;

					if (true == PlayerRenderer_DashLine->GetUpdateValue())
					{
						PlayerRenderer_DashLine->Off();
					}

					if (true == PlayerRenderer_Dash->GetUpdateValue())
					{
						PlayerRenderer_Dash->Off();
					}

					FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
					return;
				}
				// �̵��� ���� ��ȿ�� ��� �ش� ��ġ�� �÷��̾ �����Դϴ�.
				else
				{
					// �뽬 �浹ü�� �浹�� ��� Enemy�� Death ���·� �����մϴ�. 
					End = MousePos;
					PlayerDashAttackEvent();
					MainSpriteRenderer->ChangeAnimation("Dash");
					Player::MainPlayer->Transform.AddLocalPosition(ToMouse);
					Player::MainPlayer->IsOnDash = false;
				}
			}


			// ȭ�鿡 ��µǰ� �ִ� �뽬 ����, ���� ������ ��Ȱ��ȭ
			if (true == PlayerRenderer_DashLine->GetUpdateValue())
			{
				PlayerRenderer_DashLine->Off();
			}

			if (true == PlayerRenderer_Dash->GetUpdateValue())
			{
				PlayerRenderer_Dash->Off();
			}


			// �뽬 �ִϸ��̼��� ������ Idle ���·� ��ȯ�մϴ�.
			if (Player::MainPlayer->GetMainRenderer()->IsCurAnimationEnd())
			{
				//	CurPlayerDashCoolTime = MaxPlayerDashCoolTime;
				IsOnDashCoolTimeDecrease = true;
				CurPlayerDashCoolTime = 0.0f;
				FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
				return;
			}

		}

	};

	/*
		<���� �����ؾ� �ϴ� ���>
		1. �뽬 �̵� �߿� �浹�� ���Ͱ� �ִ� ��� �������� ��� �� [O]
		2. �뽬 �̵��� ������ ��Ÿ�� Ÿ�̸Ӱ� �۵��ϸ�, ��Ÿ�� ���� �ٽ� �뽬 ���¿� ������ �� ���� [O]
		3. 2�� ���°� UI�� ���� ǥ�õ� []
		4. ���� ������Ʈ�� ���͸� ���¿� �����Ѵ�. [O]
		5. ���͸��� 0�� ��쿡�� �뽬 ���¿� ������ �� ����, �����̶�� ���°� �����ȴ�. [O]
	*/

	FSM_PlayerState.CreateState(FSM_PlayerState::Dash, PlayerState_Dash_Param);
}

void Player::FSM_Player_Attack()
{
	CreateStateParameter PlayerState_Attack_Param;

	PlayerState_Attack_Param.Start = [=](class GameEngineState* _Parent)
	{
		DirCheck();

		float4 PlayerPos = Transform.GetWorldPosition();
		MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
		MouseDir = MousePos - PlayerPos;
		MouseDir.Normalize();


		float4 angle = atan2(MousePos.Y - PlayerPos.Y,
			MousePos.X - PlayerPos.X);

		float4 Rot = angle * GameEngineMath::R2D;


		//		OutputDebugStringA(Rot.ToString("\n").c_str());


		MainSpriteRenderer->Transform.SetWorldRotation({ 0.0f, 0.0f, Rot.X });

		MainSpriteRenderer->ChangeAnimation("Dash");

		// ���콺 ���⿡ ���� �÷��̾��� ������ �����մϴ�.
		if (MouseDir.X > 0.0f)
		{
			if (MouseDir.Y < 0.45f && MouseDir.Y > -0.45f)
			{
				Dir = PlayerDir::Right;
				//				OutputDebugStringA("����\n");
			}

			else if (MouseDir.Y > 0.45f)
			{
				Dir = PlayerDir::RightUp;
				//				OutputDebugStringA("�������\n");
			}

			else if (MouseDir.Y < -0.45f)
			{
				Dir = PlayerDir::RightDown;
				//				OutputDebugStringA("�����ϴ�\n");
			}

		}

		else
		{
			MainSpriteRenderer->Transform.SetWorldRotation({ 0.0f, 0.0f, Rot.X + 175.0f });

			if (MouseDir.Y < 0.45f && MouseDir.Y > -0.45f)
			{
				Dir = PlayerDir::Left;
				//				OutputDebugStringA("����\n");
			}

			else if (MouseDir.Y > 0.45f)
			{
				Dir = PlayerDir::LeftUp;
				//				OutputDebugStringA("�������\n");
			}

			else if (MouseDir.Y < -0.45f)
			{
				Dir = PlayerDir::LeftDown;
				//				OutputDebugStringA("�����ϴ�\n");
			}

		}

		std::shared_ptr<PlayerAttack> AttackObject = GetLevel()->CreateActor<PlayerAttack>();
		AttackObject->Transform.SetLocalPosition(Transform.GetWorldPosition() + (MouseDir * 100));
		AttackObject->Transform.SetWorldRotation({ 0.0f, 0.0f, Rot.X });


		GameEngineRandom Random;

		// FX ���� ���

		int SlashSoundIndex = Random.RandomInt(0, 2);

		switch (SlashSoundIndex)
		{
		case 0:
			FxPlayer = GameEngineSound::SoundPlay("sound_player_slash_1.wav");
			break;

		case 1:
			FxPlayer = GameEngineSound::SoundPlay("sound_player_slash_2.wav");
			break;

		case 2:
			FxPlayer = GameEngineSound::SoundPlay("sound_player_slash_3.wav");
			break;

		default:
			break;
		}

		if (Dir == PlayerDir::Right || Dir == PlayerDir::RightUp || Dir == PlayerDir::RightDown)
		{
			MainSpriteRenderer->RightFlip();
		}
		else if (Dir == PlayerDir::Left || Dir == PlayerDir::LeftUp || Dir == PlayerDir::LeftDown)
		{
			MainSpriteRenderer->LeftFlip();
		}
	};

	PlayerState_Attack_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		Gravity(_Delta);

		float4 MovePos = MouseDir;
		float4 CheckPos = float4::ZERO;

		if (Dir == PlayerDir::Right)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck };
			MovePos = float4::RIGHT;
		}

		else if (Dir == PlayerDir::Left)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck };
			MovePos = float4::LEFT;
		}

		else if (Dir == PlayerDir::RightUp)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck + UpCheck };
		}

		else if (Dir == PlayerDir::LeftUp)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck + UpCheck };
		}

		else if (Dir == PlayerDir::RightDown)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck + DownCheck };

			if (false == GetGroundPixelCollision())
			{
				CheckPos = { Transform.GetWorldPosition() + RightCheck };
				MovePos = float4::RIGHT;
			}
		}

		else if (Dir == PlayerDir::LeftDown)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck + DownCheck };

			if (false == GetGroundPixelCollision())
			{
				CheckPos = { Transform.GetWorldPosition() + LeftCheck };
				MovePos = float4::LEFT;
			}
		}

		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color != GameEngineColor::RED && FSM_PlayerState.GetStateTime() < 0.2f)
		{
			Transform.AddLocalPosition(MovePos * _Delta * 600.0f);
		}

		if (true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			DirCheck();

			if (Dir == PlayerDir::Left || Dir == PlayerDir::LeftDown || Dir == PlayerDir::LeftUp)
			{
				Dir = PlayerDir::Left;
			}
			else
			{
				Dir = PlayerDir::Right;
			}

			MainSpriteRenderer->ChangeAnimation("Attack");

			if (MainSpriteRenderer->IsCurAnimation("Attack") && true == MainSpriteRenderer->IsCurAnimationEnd())
			{
				MainSpriteRenderer->Transform.SetWorldRotation({ 0.0f, 0.0f, 0.0f });
				FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
				return;
			};
		}

	};


	PlayerState_Attack_Param.End = [=](class GameEngineState* _Parent)
	{

	};

	FSM_PlayerState.CreateState(FSM_PlayerState::Attack, PlayerState_Attack_Param);
}

void Player::FSM_Player_DoorKick()
{
	CreateStateParameter PlayerState_DoorKick_Param;

	PlayerState_DoorKick_Param.Start = [=](class GameEngineState* _Parent)
	{
		MainSpriteRenderer->ChangeAnimation("DoorKick");
	};

	PlayerState_DoorKick_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		Gravity(_Delta);
		DirCheck();

		if (true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
			return;
		}

	};

	FSM_PlayerState.CreateState(FSM_PlayerState::DoorKick, PlayerState_DoorKick_Param);
}