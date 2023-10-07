#include "PreCompile.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "UI_Mouse.h"

void Player::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void Player::RunStart()
{
	FxPlayer = GameEngineSound::SoundPlay("sound_player_running_1.wav");

	MainSpriteRenderer->ChangeAnimation("Run");
}

void Player::JumpStart()
{
	PlayerFXRenderer->Transform.SetLocalPosition({ 0.0f, -10.0f, 0.0f, 1.0f });
	PlayerFXRenderer->On();
	FxPlayer = GameEngineSound::SoundPlay("sound_player_jump.wav");

	//if (Dir == PlayerDir::Right)
	//{
		SetGravityVector((float4::UP) * 200.0f);
//	}

//	else
	//{
	//	SetGravityVector((float4::UP + float4::LEFT) * 200.0f);
	//}

	MainSpriteRenderer->ChangeAnimation("Jump");

	PlayerFXRenderer->ChangeAnimation("JumpCloud");
}

void Player::RollStart()
{
	MainSpriteRenderer->ChangeAnimation("Roll");
}

void Player::AttackStart()
{

	float4 PlayerPos = Transform.GetWorldPosition();
	PlayerPos.Z = 0;
	MousePos = UI_Mouse::Mouse->GetMouseWorldToActorPos();
	MousePos.Z = 0;
	MouseDir = MousePos - PlayerPos;
	MouseDir.Z = 0;

//	OutputDebugStringA(MousePos.ToString("\n").c_str());

	MainSpriteRenderer->SetImageScale({ 137, 65 });
	MainSpriteRenderer->ChangeAnimation("Dash");

	// 좌측 상단
	if (PlayerPos.X > MouseDir.X && PlayerPos.Y < MouseDir.Y)
	{
		Dir = PlayerDir::LeftUp;
		OutputDebugStringA("좌측 상단\n");
	}

	// 좌측 하단
	if (PlayerPos.X > MouseDir.X && PlayerPos.Y > MouseDir.Y)
	{
		Dir = PlayerDir::LeftDown;
		OutputDebugStringA("좌측 하단\n");
	}

	// 오른쪽 상단
	if (PlayerPos.X < MouseDir.X && PlayerPos.Y < MouseDir.Y)
	{
		Dir = PlayerDir::RightUp;
		OutputDebugStringA("오른쪽 상단\n");
	}

	// 오른쪽 상단
	if (PlayerPos.X < MouseDir.X && PlayerPos.Y > MouseDir.Y)
	{
		Dir = PlayerDir::RightDown;
		OutputDebugStringA("오른쪽 하단\n");
	}

	std::shared_ptr<PlayerAttack> AttackObject = GetLevel()->CreateActor<PlayerAttack>();

	if (Dir == PlayerDir::Right || Dir == PlayerDir::RightUp || Dir == PlayerDir::RightDown)
	{
		MainSpriteRenderer->RightFlip();
		AttackObject->Transform.SetLocalPosition({ Transform.GetWorldPosition().X + 100.0f, Transform.GetWorldPosition().Y });
	}

	else if (Dir == PlayerDir::Left || Dir == PlayerDir::LeftUp || Dir == PlayerDir::LeftDown)
	{
		MainSpriteRenderer->LeftFlip();
		AttackObject->Transform.SetLocalPosition({ Transform.GetWorldPosition().X - 100.0f, Transform.GetWorldPosition().Y });
		AttackObject->Transform.SetLocalScale({ -AttackObject->Transform.GetLocalScale().X, AttackObject->Transform.GetLocalScale().Y });
	}

}

void Player::DashStart()
{
	PlayerRenderer_Dash->On();
}

void Player::FallStart()
{
	MainSpriteRenderer->ChangeAnimation("Fall");
}

void Player::DeathStart()
{
	MainSpriteRenderer->ChangeAnimation("Death");
}

void Player::DoorKickStart()
{
	MainSpriteRenderer->ChangeAnimation("DoorKick");
}

void Player::IdleToRunStart()
{
	MainSpriteRenderer->ChangeAnimation("IdleToRun");
}

void Player::RunToIdleStart()
{
	MainSpriteRenderer->ChangeAnimation("RunToIdle");
}

void Player::PreCrouchStart()
{
	MainSpriteRenderer->ChangeAnimation("Precrouch");
}

void Player::PostCrouchStart()
{
	MainSpriteRenderer->ChangeAnimation("Postcrouch");
}

void Player::IdleUpdate(float _Delta)
{
	Gravity(_Delta);

	if (Dir == PlayerDir::Right)
	{
		//	MainSpriteRenderer->SetImageScale({ 36, 40 });
				//Transform.SetLocalScale({ 36 * 1.5f, 40 * 1.5f });
	}

	else
	{
		//	MainSpriteRenderer->SetImageScale({ -36, 40 });
	//		MainSpriteRenderer->Transform.SetLocalScale({ -36 * 1.5f, 40 * 1.5f });
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		DirCheck();
		ChangeState(PlayerState::PreCrouch);
		return;
	}

	else if (true == GameEngineInput::IsPress('S') && true == GameEngineInput::IsPress('D'))
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

//		DirCheck();
		ChangeState(PlayerState::Attack);
		return;
	}

	else if (true == GameEngineInput::IsDown(VK_RBUTTON))
	{
		ChangeState(PlayerState::Dash);
		return;
	}


}

void Player::IdleToRunUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Run);
		return;
	}
}

void Player::RunToIdleUpdate(float _Delta)
{

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{

		DirCheck();

		std::shared_ptr<PlayerAttack> AttackObject = GetLevel()->CreateActor<PlayerAttack>();

		if (Dir == PlayerDir::Right)
		{
			AttackObject->Transform.SetLocalPosition({ Transform.GetWorldPosition().X + 100.0f, Transform.GetWorldPosition().Y });
		}

		else if (Dir == PlayerDir::Left)
		{
			AttackObject->Transform.SetLocalPosition({ Transform.GetWorldPosition().X - 100.0f, Transform.GetWorldPosition().Y });
			AttackObject->Transform.SetLocalScale({ -AttackObject->Transform.GetLocalScale().X, AttackObject->Transform.GetLocalScale().Y });
		}

		ChangeState(PlayerState::Attack);
		return;
	}

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
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

	PlayerFXRenderer->On();
	PlayerFXRenderer->ChangeAnimation("RunCloud");

	if (Dir == PlayerDir::Left)
	{
		PlayerFXRenderer->Transform.SetLocalPosition({ 20.0f, -20.0f, 0.0f, 1.0f });
	}

	else if (Dir == PlayerDir::Right)
	{
		PlayerFXRenderer->Transform.SetLocalPosition({ -20.0f, -20.0f, 0.0f, 1.0f });
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
		PlayerFXRenderer->Off();
		ChangeState(PlayerState::Attack);
		return;
	}



	if (MovePos == float4::ZERO)
	{
		//DirCheck();
		PlayerFXRenderer->Off();
		ChangeState(PlayerState::RunToIdle);
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

		if (true == PlayerFXRenderer->IsCurAnimationEnd())
		{
			PlayerFXRenderer->Off();
		}

		//if (false == GetGroundPixelCollision())
		//{


		////	ChangeState(PlayerState::Idle);
		//	return;
		//}
	}

	// 점프 최상단을 떨어지는 기점으로 사용
	//if (GetGravityVector().iY() >= float4::ZERO.iY())
	//{
	//	ChangeState(PlayerState::Falling);
	//	return;
	//}

	if (GetGravityVector().Y <= -100.f)
	{
		ChangeState(PlayerState::Fall);
		return;
	}

}

void Player::RollUpdate(float _Delta)
{

	Gravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (Dir == PlayerDir::Left)
	{
		//MainSpriteRenderer->SetImageScale({ -36, 40 });
//		MainSpriteRenderer->Transform.SetLocalScale({ -108 * 0.7f, 68 * 0.7f });
	}

	else
	{
		//MainSpriteRenderer->SetImageScale({ 36, 40 });
//		MainSpriteRenderer->Transform.SetLocalScale({ 108 * 0.7f, 68 * 0.7f });
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

	if (Dir == PlayerDir::RightUp)
	{
		CheckPos = { Transform.GetWorldPosition() + RightCheck };
		MovePos = { (float4::UP + float4::RIGHT) * _Delta * Speed };
	}

	else if (Dir == PlayerDir::LeftUp)
	{
		CheckPos = { Transform.GetWorldPosition() + LeftCheck };
		MovePos = { (float4::UP + float4::LEFT) * _Delta * Speed };
	}

	else if (Dir == PlayerDir::RightDown)
	{
		CheckPos = { Transform.GetWorldPosition() + RightCheck + DownCheck };
		MovePos = { (float4::DOWN + float4::RIGHT) * _Delta * Speed };
	}

	else if (Dir == PlayerDir::LeftDown)
	{
		CheckPos = { Transform.GetWorldPosition() + LeftCheck + DownCheck };
		MovePos = { (float4::DOWN + float4::LEFT) * _Delta * Speed };
	}


	GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);

	if (Color == GameEngineColor::WHITE)
	{
		Transform.AddLocalPosition(MovePos);
	}

	else
	{
		if (Dir == PlayerDir::RightDown)
		{
			CheckPos = { Transform.GetWorldPosition() + RightCheck + DownCheck };
			MovePos = { (float4::RIGHT) * _Delta * Speed };
		}

		else if (Dir == PlayerDir::LeftDown)
		{
			CheckPos = { Transform.GetWorldPosition() + LeftCheck + DownCheck };
			MovePos = { (float4::LEFT) * _Delta * Speed };
		}

		Transform.AddLocalPosition(MovePos);
	}

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		DirCheck();

		if (Dir == PlayerDir::Left || Dir == PlayerDir::LeftDown || Dir == PlayerDir::LeftUp)
		{
		//	MainSpriteRenderer->SetImageScale({ -36, 40 });
//			MainSpriteRenderer->Transform.SetLocalScale({ -134 * 0.7f, 74 * 0.7f });
			Dir = PlayerDir::Left;
		}

		else
		{
		//	MainSpriteRenderer->SetImageScale({ 36, 40 });
//			MainSpriteRenderer->Transform.SetLocalScale({ 134 * 0.7f, 74 * 0.7f });
			Dir = PlayerDir::Right;
		}

		MainSpriteRenderer->ChangeAnimation("Attack");

		if (true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			MainSpriteRenderer->SetImageScale({ 62, 65 });
			ChangeState(PlayerState::Idle);
		}
		return;
	}
}

void Player::DashUpdate(float _Delta)
{

	float4 PlayerPos = Transform.GetWorldPosition();
	PlayerPos.Z = 0;
	MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();

	float4 test = UI_Mouse::Mouse->GetMouseWorldToActorPos() - PlayerPos;
	OutputDebugStringA(test.ToString("\n").c_str());

	//test.Y = -abs(test.Y);

	//if (test.Y < 0.0f)
	//{
	//	test.Y = abs(test.Y);
	//}

	//if (test.Y > 0.0f)
	//{
	//	test.Y = -abs(test.Y);
	//}

	float4 MouseCheckPos = MousePos - PlayerPos;


	MousePos.Z = 0;
	ToMouse = MousePos - PlayerPos;


	ToMouse.Size();

	float4 t = ToMouse;

	//		 max range
	if (t.X > 200.f)
	{
		t.X = 200.f;
	}

	if (t.X < -200.f)
	{
		t.X = -200.f;
	}

	else if (t.Y > 200.f)
	{
		t.Y = 200.f;
	}

	if (t.Y < -200.f)
	{
		t.Y = -200.f;
	}

	ToMouse.Normalize();
	ToMouse.X = abs(ToMouse.X);
	ToMouse.Y = abs(ToMouse.Y);

			// max range = 200.0f
	ToMouse *= t;
	ToMouse.Z = 0;


	if (true == GameEngineInput::IsFree(VK_RBUTTON))
	{

		// 마우스 콜리전이 위치하는 곳을 다시 확인하고 수정
		GameEngineColor ColorCheck = GetMapColor(test, GameEngineColor::WHITE);


		UI_Mouse::Mouse->MouseCollision->Transform.SetLocalPosition(test);


		if (ColorCheck == GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(ToMouse);
		}

		PlayerRenderer_Dash->Off();
		ChangeState(PlayerState::Idle);


	}


}

void Player::FallUpdate(float _Delta)
{
	Gravity(_Delta);

	if (true == GameEngineInput::IsPress('D'))
	{
		SetGravityVector((float4::DOWN + float4::RIGHT) * 200.0f);
	}

	else if (true == GameEngineInput::IsPress('A'))
	{
		SetGravityVector((float4::DOWN + float4::LEFT) * 200.0f);
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

		ChangeState(PlayerState::PostCrouch);
		return;
	}

}

void Player::DeathUpdate(float _Delta)
{
	Gravity(_Delta);

	if (Dir == PlayerDir::Right)
	{

	//	MainSpriteRenderer->SetImageScale({ 36, 54.f });
	//	MainSpriteRenderer->Transform.SetLocalScale({ 130.f, 54.f });
	}

	else
	{

	//	MainSpriteRenderer->SetImageScale({ -36.f, 54.f });
//		MainSpriteRenderer->Transform.SetLocalScale({ -130.f, 54.f });
	}
}

void Player::DoorKickUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::PreCrouchUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd() 
		&& true == GameEngineInput::IsFree('S'))
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::PostCrouchUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd() 
		&& true == GameEngineInput::IsFree('S'))
	{
		ChangeState(PlayerState::Idle);
	}
}
