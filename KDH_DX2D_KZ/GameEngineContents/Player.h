#pragma once
#include "Character.h"
#include <GameEngineCore/GameEngineState.h>

enum class FSM_PlayerState
{
	Idle,
	Run,
	Jump,
	Fall,
	PostCrouch,
	PreCrouch,
	Roll,
	Attack,
	DoorKick,
	Dash,
	Death,
	IdleToRun,
	RunToIdle,
	Default
};

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	Fall,
	PostCrouch,
	PreCrouch,
	Roll,
	Attack,
	Doorkick,
	Dash,
	Death,
	IdleToRun,
	RunToIdle,
	Default,
};

enum class PlayerDir
{
	Right,
	Left,
	RightDown,
	RightUp,
	LeftDown,
	LeftUp,
	Default,
};

class Player : public Character
{
public:
	float4 End = float4::ZERO;
	
	static Player* MainPlayer;


	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Reverse;

	bool IsUseInput = true;

	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


	// FSM
	void FSM_Player_Idle();
	void FSM_Player_Run();
	void FSM_Player_Jump();
	void FSM_Player_PreCrouch();
	void FSM_Player_Roll();
	void FSM_Player_Fall();
	void FSM_Player_Dash();
	void FSM_Player_Attack();
	void FSM_Player_DoorKick();
	void FSM_Player_RunToIdle();
	void FSM_Player_IdleToRun();
	void FSM_Player_Death();

	//


	float Speed = 500.0f;

	void SetPlayerInputUseOn()
	{
		IsUseInput = true;
	}

	void SetPlayerInputUseOff()
	{
		IsUseInput = false;
	}

	std::shared_ptr<class GameEngineSpriteRenderer> GetMainRenderer() const
	{
		return MainSpriteRenderer;
	}

	float4 ActorCameraPos()
	{
		return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	}

	bool GetPlayerDashable() const
	{
		return IsOnDash;
	}

	bool GetOnPlayerDashCoolTime() const
	{
		return IsOnDashCoolTimeDecrease;
	}

	void ChangeState(PlayerState State);

	void StateUpdate(float _Delta);

	void DirCheck();

	void SetPlayerDir(PlayerDir _PlayerDir)
	{
		Dir = _PlayerDir;
	}

	float4 GetPlayerDir() const
	{

		if (Dir == PlayerDir::Left)
		{
			return float4::LEFT;
		}
		else if (Dir == PlayerDir::Right)
		{
			return float4::RIGHT;
		}
		else
		{
			return float4::ZERO;
		}

	}

	PlayerDir GetPlayerDirEnum() const
	{
		return Dir;
	}

	void PlayerDamagedEvent();
	void PlayerParryEvent();
	void PlayerBossParryEvent();
	void PlayerDashAttackEvent();
	void PlayerBossGrenadeDamagedEvent();
	void PlayerBossAttackKnockBackEvent();

	void OnParryable()
	{
		IsParryable = true;
	}
	void OffParryable()
	{
		IsParryable = false;
	}
	bool GetParryable()
	{
		return IsParryable;
	}

	void IdleStart();
	void IdleUpdate(float _Delta);

	void IdleToRunStart();
	void IdleToRunUpdate(float _Delta);

	void RunToIdleStart();
	void RunToIdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void RollStart();
	void RollUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DashStart();
	void DashUpdate(float _Delta);

	void FallStart();
	void FallUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void DoorKickStart();
	void DoorKickUpdate(float _Delta);

	void PreCrouchStart();
	void PreCrouchUpdate(float _Delta);

	void PostCrouchStart();
	void PostCrouchUpdate(float _Delta);

	std::shared_ptr<GameEngineSpriteRenderer> PlayerRenderer_Dash;
	std::shared_ptr<GameEngineSpriteRenderer> PlayerRenderer_DashLine;

	bool IsParryable = false;
	bool IsDeath = false;

	float GetCurrentDashCoolTime() const
	{
		return CurPlayerDashCoolTime;
	}

	float GetMaxDashCoolTime() const
	{
		return MaxPlayerDashCoolTime;
	}

	float4 GetPlayerAttackRotation() const
	{
		return PlayerAttackRot;
	}


	void Update_PlayerDashCoolTime(float _Delta);

	bool Get_PlayerDashable()
	{
		return IsDashable;
	}

	void On_PlayerDashable()
	{
		IsDashable = true;
	}

	void Off_PlayerDashable()
	{
		IsDashable = false;
	}

//	PlayerDir Dir = PlayerDir::Right;

		// 새로운 FSM 적용
	GameEngineState FSM_PlayerState;

	GameEngineSoundPlayer FxPlayer;

	float4 PlayerAttackRot = float4::ZERO;	
	float4 MouseDir = float4::ZERO;

protected:
	void Start() override;
	void Update(float _Delta) override;

	PlayerDir Dir = PlayerDir::Right;
//	std::string CurState = "";




	PlayerState State = PlayerState::Default;


private:

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerFXRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerCursorSlashRenderer;

	std::shared_ptr<class GameEngineCollision> PlayerBodyCollision;
	std::shared_ptr<class GameEngineCollision> PlayerParryingCollision;
	std::shared_ptr<class GameEngineCollision> PlayerDashCollision;



	////////////////////// DebugValue

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Left;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Right;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Up;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Down;

	// y값은 반전되므로 주의할 것
	float4 LeftCheck = { -40.0f, 0.0f };
	float4 RightCheck = { 40.0f, 0.0f };
	float4 UpCheck = { 0.0f, 40.0f };
	float4 DownCheck = { 0.f, -40.0f };

	float4 RightUpCheck = { 40.0f, 50.0f };
	float4 LeftUpCheck = { -40.0f, 50.0f };

	float4 RightDownCheck = { 40.0f, -40.0f };
	float4 LeftDownCheck = { -40.0f, -37.0f };

	//float4 UpCheck = { 0.f, 40.0f };
	//float4 DownCheck = { 0.f, -40.0f };

	float4 MousePos = float4::ZERO;
	float4 ToMouse = float4::ZERO;
	float4 MoveVec = float4::ZERO;

	float4 FXPos = float4::ZERO;

	bool IsOnDash = false;
	bool IsDashable = true;

	float MaxPlayerDashCoolTime = 1.0f;
	float CurPlayerDashCoolTime = 0.0f;
	bool IsOnDashCoolTimeDecrease = false;
};