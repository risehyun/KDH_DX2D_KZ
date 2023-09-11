#include "PreCompile.h"
#include "Player.h"


void Player::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void Player::RunStart()
{
	MainSpriteRenderer->ChangeAnimation("Run");
}

void Player::JumpStart()
{
	MainSpriteRenderer->ChangeAnimation("Jump");
}

void Player::RollStart()
{
	MainSpriteRenderer->ChangeAnimation("Roll");
}

void Player::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Dash");
}

void Player::DashStart()
{
	PlayerRenderer_Dash->On();

}

void Player::FallStart()
{
	MainSpriteRenderer->ChangeAnimation("Fall");
}


void Player::IdleUpdate(float _Delta)
{
	Gravity(_Delta);

	if (Dir == PlayerDir::Right)
	{
		MainSpriteRenderer->Transform.SetLocalScale({ 36 * 1.5f, 40 * 1.5f });
	}

	else
	{
		MainSpriteRenderer->Transform.SetLocalScale({ -36 * 1.5f, 40 * 1.5f });
	}


	if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Roll);
		return;
	}

	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		DirCheck();
		ChangeState(PlayerState::Roll);
		return;
	}

	else if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}

	else if (true == GameEngineInput::IsDown('W'))
	{
		DirCheck();
		ChangeState(PlayerState::Jump);
		return;
	}

	else if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	else if (true == GameEngineInput::IsDown(VK_RBUTTON))
	{
		ChangeState(PlayerState::Dash);
		return;
	}


}

void Player::RunUpdate(float _Delta)
{
	Gravity(_Delta);

	if (true == GameEngineInput::IsPress('W'))
	{
		DirCheck();
		ChangeState(PlayerState::Jump);
		return;
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;



	if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Roll);
		return;
	}

	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('A'))
	{
		DirCheck();
		ChangeState(PlayerState::Roll);
		return;
	}

	else if (true == GameEngineInput::IsPress('A'))
	{
		CheckPos = { Transform.GetWorldPosition() + LeftCheck };
		MovePos = { -Speed * _Delta, 0.0f };
	}

	else if (true == GameEngineInput::IsPress('D'))
	{
		CheckPos = { Transform.GetWorldPosition() + RightCheck };
		MovePos = { float4::RIGHT * _Delta * Speed };
	}

	else if (true == GameEngineInput::IsPress('S'))
	{
		CheckPos = { Transform.GetWorldPosition() + DownCheck };
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::Attack);
		return;
	}



	if (MovePos == float4::ZERO)
	{
		//DirCheck();
		ChangeState(PlayerState::Idle);
	}

	{
		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);
		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(MovePos);
		}

	}

}

void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;


	CheckPos = { Transform.GetWorldPosition() + UpCheck };
	MovePos = { 0.0f, float4::UP.Y * Speed * _Delta };

	//if (MovePos.Y < 0.f)
	//{
	//	ChangeState(PlayerState::Fall);
	//}

	if (true == GameEngineInput::IsPress('D'))
	{
//		SetGravityVector((float4::UP * 200.0f + float4::RIGHT) * 300.0f);
		MovePos = { (float4::RIGHT + float4::UP) * Speed * _Delta };
	}

	else if (true == GameEngineInput::IsPress('A'))
	{
//		SetGravityVector(float4::UP * 200.0f + float4::LEFT * 300.0f);
		MovePos = { (float4::LEFT + float4::UP) * Speed * _Delta };
	}

	else if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	{
		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(MovePos);
		}

		else
		{
			ChangeState(PlayerState::Fall);

		}

		if (false == GetGroundPixelCollision())
		{
			ChangeState(PlayerState::Idle);
			return;
		}
	}
}

void Player::RollUpdate(float _Delta)
{

	Gravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;



	if (Dir == PlayerDir::Left)
	{
		MainSpriteRenderer->Transform.SetLocalScale({ -108 * 0.7f, 68 * 0.7f });
	}

	else
	{
		MainSpriteRenderer->Transform.SetLocalScale({ 108 * 0.7f, 68 * 0.7f });
	}



	if (true == GameEngineInput::IsPress('D'))
	{
		CheckPos = { Transform.GetWorldPosition() + RightCheck };
		MovePos = { float4::RIGHT * _Delta * Speed };
	}

	else if (true == GameEngineInput::IsPress('A'))
	{
		CheckPos = { Transform.GetWorldPosition() + LeftCheck };
		MovePos = { float4::LEFT * _Delta * Speed };
	}



	{
		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(MovePos);
		}

		if (/*false == GetGroundPixelCollision() || */true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			ChangeState(PlayerState::Idle);
			return;
		}

	}

}

void Player::AttackUpdate(float _Delta)
{

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	DirCheck();

	if (Dir == PlayerDir::Right)
	{
		CheckPos = { Transform.GetWorldPosition() + RightCheck };
		MovePos = { (float4::UP + float4::RIGHT) * _Delta * Speed };
	}

	else
	{
		CheckPos = { Transform.GetWorldPosition() + LeftCheck };
		MovePos = { (float4::UP + float4::LEFT) * _Delta * Speed };
	}


	GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

	if (Color == GameEngineColor::WHITE)
	{
		Transform.AddLocalPosition(MovePos);
	}

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{

		if (Dir == PlayerDir::Left)
		{
			MainSpriteRenderer->Transform.SetLocalScale({ -134 * 0.7f, 74 * 0.7f });
		}

		else
		{
			MainSpriteRenderer->Transform.SetLocalScale({ 134 * 0.7f, 74 * 0.7f });
		}

		MainSpriteRenderer->ChangeAnimation("Attack");

		if (true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			ChangeState(PlayerState::Idle);
		}
		return;
	}
}

void Player::DashUpdate(float _Delta)
{
	if (true == GameEngineInput::IsFree(VK_RBUTTON))
	{
		PlayerRenderer_Dash->Off();
		ChangeState(PlayerState::Idle);
	}


}

void Player::FallUpdate(float _Delta)
{
	
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	DirCheck();

	if (Dir == PlayerDir::Right)
	{
		CheckPos = { Transform.GetWorldPosition() + DownCheck };
		MovePos = { (float4::DOWN + float4::RIGHT) * _Delta * (Speed/2) };

	}

	else
	{
		CheckPos = { Transform.GetWorldPosition() + DownCheck };
		MovePos = { (float4::DOWN + float4::LEFT) * _Delta * (Speed / 2) };
	}


	GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

	if (Color == GameEngineColor::WHITE)
	{
		Transform.AddLocalPosition(MovePos);
	}



//	Gravity(_Delta);

	if (false == GetGroundPixelCollision())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

}
