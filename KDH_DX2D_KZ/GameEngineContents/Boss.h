#pragma once
#include "Character.h"
#include <GameEngineCore/GameEngineState.h>

enum class FSM_BossState
{
	Idle,
	GroundRifleAttack_Start,
	GroundRifleAttack_End,
	AirRifleAttack_Start,
	AirRifleAttack_End,
	Death,
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
	static Boss* Boss_HeadHunter;

public:
	Boss();
	~Boss();

	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

	void DirCheck();

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

	// 새로운 FSM 적용
	GameEngineState FSM_BossState;

	float Speed = 200.0f;

protected:
	void Start() override;
	void Update(float _Delta) override;

	BossDir Dir = BossDir::Right;

private:
	void FSM_Boss_Idle();
	void FSM_Boss_Death();
	void FSM_Boss_GroundRifleAttack();
	void FSM_Boss_GroundRifleAttackEnd();

	void FSM_Boss_AirRifleAttack();
	void FSM_Boss_AirRifleAttackEnd();

	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> BossMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> BossEffectRenderer;

	std::shared_ptr<class GameEngineCollision> BossMainCollision;
	std::shared_ptr<class GameEngineCollision> BossDetectCollision;

	void BossDamagedEvent();
	void BossPlayerDetectEvent();

	////////////////////// DebugValue
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Left;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Right;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Up;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Down;

	// y값은 반전되므로 주의할 것
	float4 LeftCheck = { -30.0f, 0.0f };
	float4 RightCheck = { 30.0f, 0.0f };
	float4 UpCheck = { 0.f, 30.0f };
	float4 DownCheck = { 0.f, -50.0f };

	float4 AttackFireInitPos = float4::ZERO;
	float4 AttackFireDir = float4::ZERO;

	float4 CheckPos = float4::ZERO;

};

