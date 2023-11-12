#pragma once
#include "Character.h"
#include <GameEngineCore/GameEngineState.h>

enum class FSM_BossState
{
	Idle,
	GroundRifleAttack_Start,
	GroundRifleAttack_End,
	AirRifleAttack_Start,
	AirRifleAttack,
	AirRifleAttack_End,
	MultipleAirRifleAttack_Start,
	MultipleAirRifleAttack_End,
	GroundDashAttack,
	AirDashAttack,
	WallJumpAttack_Start,
	WallJumpAttack,
	WallJumpAttack_End,
	GrenadeAttack_Start,
	GrenadeAttack,
	GrenadeAttack_End,
	WallTurretAttack,
	SuicideBombingAttack_Start,
	SuicideBombingAttack,
	DodgeRoll,
	Hurt,
	Fall,
	Death,
	DieLand,
	Crawl,
	Default,
};

enum class BossDir
{
	Right,
	Left,
	Default,
};

class Boss : public Character
{
public:

	static Boss* Boss_HeadHunter;

	Boss();
	~Boss();

	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

	void DirCheck();

	void SetBossActivate()
	{
		BossMainRenderer->On();
		BossMainCollision->On();
	}

	void SetBossDeactivate()
	{
		BossMainRenderer->Off();
		BossMainCollision->Off();
	}

	std::shared_ptr<GameEngineSpriteRenderer> GetMainRenderer() const
	{
		return BossMainRenderer;
	}

	std::shared_ptr<GameEngineCollision> GetMainCollision() const
	{
		return BossMainCollision;
	}

	float4 GetBossDir() const
	{
		if (Dir == BossDir::Left)
		{
			return float4::LEFT;
		}

		else if (Dir == BossDir::Right)
		{
			return float4::RIGHT;
		}

	}

	void SpawnWallTurretEvent(GameEngineRenderer* _Renderer);
	void ResetEvent(GameEngineRenderer* _Renderer);

	int GetBossHp() const
	{
		return BossHp;
	}

	void SetBossHp(int _NewBossHp)
	{
		BossHp = _NewBossHp;
	}


	// 새로운 FSM 적용
	GameEngineState FSM_BossState;

	float Speed = 200.0f;

protected:
	void Start() override;
	void Update(float _Delta) override;

	BossDir Dir = BossDir::Right;

private:
	void FSM_Boss_Idle();

	void FSM_Boss_GroundRifleAttack();
	void FSM_Boss_GroundRifleAttackEnd();

	void FSM_Boss_AirRifleAttack_Start();
	void FSM_Boss_AirRifleAttack();
	void FSM_Boss_AirRifleAttackEnd();

	void FSM_Boss_MultipleAirRifleAttack();

	void FSM_Boss_GroundDashAttack();
	void FSM_Boss_AirDashAttack();

	void FSM_Boss_WallJump_Start();
	void FSM_Boss_WallJump();
	void FSM_Boss_WallJump_End();

	void FSM_Boss_GrenadeAttack_Start();
	void FSM_Boss_GrenadeAttack();
	void FSM_Boss_GrenadeAttack_End();

	void FSM_Boss_WallTurretAttack();

	void FSM_Boss_SuicideBombingAttack_Start();
	void FSM_Boss_SuicideBombingAttack();

	void FSM_Boss_DodgeRoll();

	void FSM_Boss_Hurt();
	void FSM_Boss_Fall();

	void FSM_Boss_Crawl();
	void FSM_Boss_DieLand();
	void FSM_Boss_Death();

	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> BossMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> BossEffectRenderer;

	std::shared_ptr<class GameEngineCollision> BossMainCollision;
	std::shared_ptr<class GameEngineCollision> BossDetectCollision;

	void BossDamagedEvent();
	void BossSelfDamagedEvent();

	////////////////////// DebugValue
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Left;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Right;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Up;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Down;

	// y값은 반전되므로 주의할 것
	float4 LeftCheck = { -30.0f, 0.0f };
	float4 RightCheck = { 30.0f, 0.0f };
	float4 UpCheck = { 0.f, 30.0f };
	float4 DownCheck = { 0.f, -40.0f };

	float4 AttackFireInitPos = float4::ZERO;
	float4 AttackFireDir = float4::ZERO;

	float4 CheckPos = float4::ZERO;
	float4 MovePos = float4::ZERO;

	float4 Dis = float4::ZERO;

	int AngleInterval = 10;
	int FireAngle = 160;

	float WallJumpTimer = 0.0f;
	float BasePatternTimer = 0.0f;

	bool IsUsingAutoPattern = false;
	bool IsEndJumpAttack = false;

	int GrenadeAttackCount = 0;
	int BossHp = 3;
	int AirRifleAttackCount = 1;

	std::vector<std::shared_ptr<class BossBullet>> AllBullet;
	GameEngineSoundPlayer ExplosionFxPlayer;
	GameEngineSoundPlayer FxPlayer;
};

