#pragma once
#include "Character.h"


enum class EnemyState
{
	Idle,
	Run,
	Attack,
	Dash,
	Death,
	Default,
};

enum class EnemyDir
{
	Right,
	Left,
	Default,
};



class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

	void ChangeState(EnemyState State);

	void StateUpdate(float _Delta);

	void DirCheck();

	void ChangeAnimationState(std::string_view _StateName);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	EnemyState State = EnemyState::Default;
	EnemyDir Dir = EnemyDir::Right;
	std::string CurState = "";

private:
	std::shared_ptr<class GameEngineSpriteRenderer> EnemyMainRenderer;
	std::shared_ptr<GameEngineCollision> EnemyMainCollision;

	float Speed = 200.0f;

	////////////////////// DebugValue

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Left;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Right;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Up;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Down;

	// y값은 반전되므로 주의할 것
	float4 LeftCheck = { -30.0f, 0.0f };
	float4 RightCheck = { 30.0f, 0.0f };
	float4 UpCheck = { 0.f, 30.0f };
	float4 DownCheck = { 0.f, -30.0f };
};

