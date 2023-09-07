#include "PreCompile.h"
#include "Player.h"


void Player::IdleStart()
{
//	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
}

void Player::JumpStart()
{
}


void Player::IdleUpdate(float _Delta)
{


	//GameEngineColor Color = GetMapColor(float4::ZERO, GameEngineColor::WHITE);
	//if (GameEngineColor::WHITE == Color)
	//{
		Gravity(_Delta);
	//}

	//else
	//{
	//	GameEngineColor CheckColor = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 30.0f}, GameEngineColor::WHITE);

	//	while (CheckColor != GameEngineColor::WHITE)
	//	{
	//		Transform.AddLocalPosition(float4::UP);
	//	}

	//	CheckColor = GetMapColor(float4::DOWN, GameEngineColor::WHITE);

	//	while (CheckColor != GameEngineColor::WHITE)
	//	{
	//		CheckColor = GetMapColor(float4::DOWN, GameEngineColor::WHITE);
	//		Transform.AddLocalPosition(float4::DOWN);
	//	}

	//	GravityReset();
	//}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}


}

void Player::RunUpdate(float _Delta)
{
	float Speed = 400.0f;

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

	else if (true == GameEngineInput::IsPress('W'))
	{
		CheckPos = { Transform.GetWorldPosition() + UpCheck };
		MovePos = { 0.0f, Speed * _Delta };
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
}