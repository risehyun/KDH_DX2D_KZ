#include "PreCompile.h"
#include <GameEngineCore/GameEngineState.h>

#include "Player.h"
#include "UI_Mouse.h"


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
		if (GameEngineInput::IsDown(VK_RBUTTON, this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Dash);
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
		Gravity(_Delta);

		//Speed = 300.0f;
		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		//static float JumpTime = 0.0f;

		//JumpTime += _Delta;

		//if (JumpTime > 2.0f)
		//{
		//	FSM_PlayerState.ChangeState(FSM_PlayerState::Fall);
		//	JumpTime = 0.0f;
		//	return;
		//}
		//else
		//{
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

		//if (Dir == PlayerDir::Left)
		//{
		//	PlayerFXRenderer->Transform.SetLocalPosition({ 20.0f, -20.0f, 0.0f, 1.0f });
		//}

		//else if (Dir == PlayerDir::Right)
		//{
		//	PlayerFXRenderer->Transform.SetLocalPosition({ -20.0f, -20.0f, 0.0f, 1.0f });
		//}


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

		if (GameEngineInput::IsDown(VK_LBUTTON, this))
		{
			PlayerFXRenderer->Off();
			//	FSM_PlayerState.ChangeState(FSM_PlayerState::Attack);
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
	};

	PlayerState_Dash_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// Dash ������ ���� �߷�, ���� ������ �ۿ��մϴ�.
		Gravity(_Delta);
		DirCheck();

		// ��ġ ����� ���� ���� �� ����
		float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
		MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();

		// Ŭ���� ��ġ�� ����մϴ�.
		float4 PlayerNextPos = UI_Mouse::Mouse->GetMouseWorldToActorPos() - PlayerPos;

		// �뽬 ������ ��Ȱ�� ���¸� Ȱ��ȭ�Ͽ� ȭ�鿡 ���̵��� �մϴ�.
		if (false == PlayerRenderer_DashLine->GetUpdateValue())
		{
			PlayerRenderer_DashLine->On();
		}

		// ���� ���� ���
		float4 RenderLinePos = PlayerRenderer_DashLine->Transform.GetLocalPosition();
		float4 MouseCheckPos = MousePos - RenderLinePos;

		float4 angle = atan2(MousePos.Y - RenderLinePos.Y,
			MousePos.X - RenderLinePos.X * GameEngineMath::R2D);

		// ����׿�
		OutputDebugStringA(angle.ToString("\n").c_str());

		ToMouse = MousePos - PlayerPos;
		ToMouse.Size();

		float4 t = ToMouse;

		//	�̵� ������ max range = 200.0f, min range = -200.0f �� ����� �ʵ��� �����մϴ�.
		if (t.X > 200.0f)
		{
			t.X = 200.0f;
		}

		if (t.X < -200.0f)
		{
			t.X = -200.0f;
		}

		else if (t.Y > 200.0f)
		{
			t.Y = 200.0f;
		}

		if (t.Y < -200.0f)
		{
			t.Y = -200.0f;
		}

		ToMouse.Normalize();
		ToMouse.X = abs(ToMouse.X);
		ToMouse.Y = abs(ToMouse.Y);

		ToMouse *= t;

		// ������ ����� ���� ���� ������ ����մϴ�.
		PlayerRenderer_DashLine->SetPivotType(PivotType::Left);
		PlayerRenderer_DashLine->Transform.SetLocalScale({ ToMouse.X / 3.0f, 2.0f, 1.0f });

		PlayerRenderer_DashLine->Transform.AddLocalRotation({ 0.0f, 0.0f, 1.0f });


		// ��ư�� ���� �ִ� ���� �̵� ������ ��ȿ���� Ȯ���� ��,
		// �ռ� ���� ��ġ�� �÷��̾ �̵��մϴ�.
		if (true == GameEngineInput::IsFree(VK_RBUTTON, this))
		{
			while (true == Player::MainPlayer->IsOnDash)
			{
				GameEngineColor ColorCheck = 
					Player::MainPlayer->GetMapColor(PlayerNextPos, GameEngineColor::WHITE);

			//	UI_Mouse::Mouse->MouseCollision->Transform.SetLocalPosition(PlayerNextPos);

				if (ColorCheck != GameEngineColor::WHITE)
				{
					IsOnDash = false;
				}
				else
				{
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

			PlayerRenderer_Dash->Off();


			// �뽬 �ִϸ��̼��� ������ Idle ���·� ��ȯ�մϴ�.
			if (Player::MainPlayer->GetMainRenderer()->IsCurAnimationEnd())
			{
				FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
				return;
			}

		}

	};

	/*
	    <���� �����ؾ� �ϴ� ���>
		1. �뽬 �̵� �߿� �浹�� ���Ͱ� �ִ� ��� �������� ��� ��
		2. �뽬 �̵��� ������ ��Ÿ�� Ÿ�̸Ӱ� �۵��ϸ�, ��Ÿ�� ���� �ٽ� �뽬 ���¿� ������ �� ����
	*/

	FSM_PlayerState.CreateState(FSM_PlayerState::Dash, PlayerState_Dash_Param);
}