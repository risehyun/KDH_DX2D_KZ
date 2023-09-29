#pragma once
#include "Character.h"

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
	static Player* MainPlayer;

	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void CameraFocus();

	float4 ActorCameraPos()
	{
		return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
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

	}

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

	bool IsParryable = false;

//	PlayerDir Dir = PlayerDir::Right;

protected:
	void Start() override;
	void Update(float _Delta) override;

	PlayerState State = PlayerState::Default;
	PlayerDir Dir = PlayerDir::Right;
	std::string CurState = "";

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

	std::shared_ptr<class GameEngineCollision> PlayerBodyCollision;

	std::shared_ptr<class GameEngineCollision> PlayerParryingCollision;

	float Speed = 300.0f;

	////////////////////// DebugValue

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Left;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Right;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Up;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Down;

	// y값은 반전되므로 주의할 것
	float4 LeftCheck = { -40.0f, 0.0f };
	float4 RightCheck = { 40.0f, 0.0f };
	float4 UpCheck = { 0.f, 40.0f };
	float4 DownCheck = { 0.f, -40.0f };

	float4 MousePos = float4::ZERO;
	float4 MouseDir = float4::ZERO;
	float4 ToMouse = float4::ZERO;
	float4 MoveVec = float4::ZERO;


};