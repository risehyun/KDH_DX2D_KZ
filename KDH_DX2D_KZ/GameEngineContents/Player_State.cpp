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


void Player::IdleUpdate(float _Delta)
{

	Gravity(_Delta);

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}


	if (true == GameEngineInput::IsDown('W'))
	{
		DirCheck();
		ChangeState(PlayerState::Jump);
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

	if (true == GameEngineInput::IsPress('A'))
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


	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { (float4::RIGHT + float4::UP) * Speed * _Delta };
	}

	else if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { (float4::LEFT + float4::UP) * Speed * _Delta };
	}




	{
		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(MovePos);
		}

		if (false == GetGroundPixelCollision())
		{
			ChangeState(PlayerState::Idle);
			return;
		}

	}

}