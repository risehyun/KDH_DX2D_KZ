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
		// Idle 상태인 동안에는 중력이 작용합니다.
		Gravity(_Delta);
		DirCheck();

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// <위로 가는 키를 눌렀을 때>
		// 위로 가는 키를 누르면 Jump 상태에 진입합니다.
		if (GameEngineInput::IsDown('W', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Jump);
			return;
		}

		// <아래로 가는 키를 눌렀을 때>
		// 아래 키를 누르는 동안은 PreCrouch 상태에 진입하거나,
		// 바로 아래쪽 픽셀을 검사해 색깔이 푸른색은 경우에는 Fall 상태로 진입합니다.
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

			// 허공인 하얀색도 아니고, 아래로 이동이 가능한 파란색도 아니라면 (기본적으로 빨강일 것)
			else
			{
				// 숙이기가 기본이고, 구르기로 전환이 가능해지는 PreCrouch 상태로 변환하고 리턴합니다.
				FSM_PlayerState.ChangeState(FSM_PlayerState::PreCrouch);
				return;
			}
		}

		// 왼쪽 혹은 오른쪽 이동 버튼을 누르면 이동(Run) 상태로 변환하고 리턴합니다.
		if (GameEngineInput::IsDown('A', this) || GameEngineInput::IsDown('D', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Run);
			return;
		}

		// 오른쪽 마우스 버튼을 누르면 대쉬 상태로 변환하고 리턴합니다.
		if (GameEngineInput::IsDown(VK_RBUTTON, this)
			&& CurPlayerDashCoolTime <= 0.0f
			&& GameStateManager::GameState->GetCurTimeControlBattery() >= 0)
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Dash);
			return;
		}

		// 왼쪽 마우스 버튼을 누르면 공격 상태로 변환하고 리턴합니다.
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

		// 이전 테스트 값은 -100.0f
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
		// PreCrouch 상태인 동안에는 중력이 작용합니다.
		Gravity(_Delta);
		DirCheck();

		// PreCrouch 상태에서 옆으로 가는 방향키를 누르면 구르기(Roll) 상태로 전환합니다.
		if (GameEngineInput::IsDown('D', this) || GameEngineInput::IsDown('A', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Roll);
			return;
		}

		// 키를 떼면 Idle 상태로 변경
		if (GameEngineInput::IsFree('S', this))
		{
			FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
			return;
		}


	};

	FSM_PlayerState.CreateState(FSM_PlayerState::PreCrouch, PlayerState_PreCrouch_Param);
}

// ★ 구르기를 할 때 Dust 발생
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
		// PreCrouch 상태인 동안에는 중력이 작용합니다.
		Gravity(_Delta);
		DirCheck();

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// 구르기를 하는 동안 속도는 평소보다 약간 더 빨라집니다. 기본값 : 300
		// ★ 변수를 상수로 할당하지 말고 따로 저장해서 할당할 것
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

		// 구르기 모션이 끝나면
		if (GetMainRenderer()->IsCurAnimationEnd())
		{
			// 속도를 원래대로 낮춰줍니다.
			Speed = 300.0f;

			// Idle 상태로 전환합니다.
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
		// PreCrouch 상태인 동안에는 중력이 작용합니다.
		Gravity(_Delta);
		DirCheck();

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		// 왼쪽 마우스 버튼을 누르면 공격 상태로 변환하고 리턴합니다.
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

		// 더 이상 입력이 없으면 멈춘 것으로 간주하고 Idle 상태로 변환 후 리턴합니다.
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

			// 대쉬 라인이 비활성 상태면 활성화하여 화면에 보이도록 합니다.
		if (false == PlayerRenderer_DashLine->GetUpdateValue())
		{
			PlayerRenderer_DashLine->On();
		}
	};

	PlayerState_Dash_Param.Stay = [=](float _Delta, class GameEngineState* _Parent)
	{
		// Dash 상태인 동안 중력, 방향 설정이 작용합니다.
		Gravity(_Delta);
		DirCheck();

		if (GameStateManager::GameState->GetCurTimeControlBattery() < 0)
		{
			// ★ Reset Dash State 같은 함수로 따로 빼서 사용
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

		// 위치 계산을 위한 변수 값 지정
		float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
		MousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();

		// 클릭한 위치를 계산합니다.
		float4 PlayerNextPos = UI_Mouse::Mouse->GetMouseWorldToActorPos() - PlayerPos;

		// 라인 범위 계산
		float4 RenderLinePos = Transform.GetWorldPosition();

		float4 angle = atan2(MousePos.Y - RenderLinePos.Y,
			MousePos.X - RenderLinePos.X);

		// 디버그용
		// OutputDebugStringA(angle.ToString("\n").c_str());

		ToMouse = MousePos - RenderLinePos;
		ToMouse.Size();

		//	이동 범위가 max range, min range를 벗어나지 않도록 보간합니다.
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

		// 위에서 계산한 값에 맞춰 라인을 출력합니다.
		PlayerRenderer_DashLine->SetPivotType(PivotType::Left);
		PlayerRenderer_DashLine->Transform.SetWorldScale({ ToMouse.Size() / 4.0f , 2.0f, 1.0f });
		PlayerRenderer_DashLine->Transform.SetWorldRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });
		PlayerRenderer_DashLine->Transform.SetWorldPosition(PlayerPos);

		PlayerDashCollision->Transform.SetWorldScale({ ToMouse.Size(), 2.0f, 1.0f });
		PlayerDashCollision->Transform.SetWorldRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });
		PlayerDashCollision->Transform.SetWorldPosition(PlayerPos);

		//PlayerRenderer_DashLine->Transform.SetLocalScale({ 20.0f, 20.0f, 1.0f });
		//PlayerRenderer_DashLine->Transform.SetWorldPosition(Transform.GetWorldPosition());


		// 버튼을 떼고 있는 동안 이동 지점이 유효한지 확인한 뒤,
		// 앞서 계산된 위치로 플레이어가 이동합니다.
		if (true == GameEngineInput::IsFree(VK_RBUTTON, this))
		{

			while (true == Player::MainPlayer->IsOnDash)
			{
				GameEngineColor ColorCheck =
					Player::MainPlayer->GetMapColor(PlayerNextPos, GameEngineColor::WHITE);

				//  디버그용
				//	UI_Mouse::Mouse->MouseCollision->Transform.SetLocalPosition(PlayerNextPos);

					// 이동할 곳이 유효 범위가 아닌 경우 Dash 상태를 취소합니다.
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
				// 이동할 곳이 유효한 경우 해당 위치로 플레이어를 움직입니다.
				else
				{
					// 대쉬 충돌체와 충돌된 모든 Enemy를 Death 상태로 변경합니다. 
					End = MousePos;
					PlayerDashAttackEvent();
					MainSpriteRenderer->ChangeAnimation("Dash");
					Player::MainPlayer->Transform.AddLocalPosition(ToMouse);
					Player::MainPlayer->IsOnDash = false;
				}
			}


			// 화면에 출력되고 있는 대쉬 범위, 라인 렌더러 비활성화
			if (true == PlayerRenderer_DashLine->GetUpdateValue())
			{
				PlayerRenderer_DashLine->Off();
			}

			if (true == PlayerRenderer_Dash->GetUpdateValue())
			{
				PlayerRenderer_Dash->Off();
			}


			// 대쉬 애니메이션이 끝나면 Idle 상태로 전환합니다.
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
		<추후 보강해야 하는 기능>
		1. 대쉬 이동 중에 충돌한 몬스터가 있는 경우 데미지를 줘야 함 [O]
		2. 대쉬 이동이 끝나면 쿨타임 타이머가 작동하며, 쿨타임 동안 다시 대쉬 상태에 진입할 수 없음 [O]
		3. 2번 상태가 UI를 통해 표시됨 []
		4. 게임 스테이트의 배터리 상태와 연동한다. [O]
		5. 배터리가 0인 경우에는 대쉬 상태에 진입할 수 없고, 도중이라면 상태가 해제된다. [O]
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

		// 마우스 방향에 따라 플레이어의 방향을 결정합니다.
		if (MouseDir.X > 0.0f)
		{
			if (MouseDir.Y < 0.45f && MouseDir.Y > -0.45f)
			{
				Dir = PlayerDir::Right;
				//				OutputDebugStringA("우측\n");
			}

			else if (MouseDir.Y > 0.45f)
			{
				Dir = PlayerDir::RightUp;
				//				OutputDebugStringA("우측상단\n");
			}

			else if (MouseDir.Y < -0.45f)
			{
				Dir = PlayerDir::RightDown;
				//				OutputDebugStringA("우측하단\n");
			}

		}

		else
		{
			MainSpriteRenderer->Transform.SetWorldRotation({ 0.0f, 0.0f, Rot.X + 175.0f });

			if (MouseDir.Y < 0.45f && MouseDir.Y > -0.45f)
			{
				Dir = PlayerDir::Left;
				//				OutputDebugStringA("좌측\n");
			}

			else if (MouseDir.Y > 0.45f)
			{
				Dir = PlayerDir::LeftUp;
				//				OutputDebugStringA("좌측상단\n");
			}

			else if (MouseDir.Y < -0.45f)
			{
				Dir = PlayerDir::LeftDown;
				//				OutputDebugStringA("좌측하단\n");
			}

		}

		std::shared_ptr<PlayerAttack> AttackObject = GetLevel()->CreateActor<PlayerAttack>();
		AttackObject->Transform.SetLocalPosition(Transform.GetWorldPosition() + (MouseDir * 100));
		AttackObject->Transform.SetWorldRotation({ 0.0f, 0.0f, Rot.X });


		GameEngineRandom Random;

		// FX 랜덤 재생

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