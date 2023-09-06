#include "PreCompile.h"
#include "Player.h"


void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
}

void Player::JumpStart()
{
}


void Player::IdleUpdate(float _Delta)
{


	GameEngineColor Color = GetMapColor(float4::ZERO, GameEngineColor::WHITE);
	if (GameEngineColor::WHITE == Color)
	{

	}

	else
	{
		GameEngineColor CheckColor = GetMapColor(float4::UP, GameEngineColor::WHITE);

		while (CheckColor != GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(float4::UP);
		}

		CheckColor = GetMapColor(float4::DOWN, GameEngineColor::WHITE);

		while (CheckColor != GameEngineColor::WHITE)
		{
//			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
			Transform.AddLocalPosition(float4::DOWN);
		}
	}

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
}

void Player::JumpUpdate(float _Delta)
{
}