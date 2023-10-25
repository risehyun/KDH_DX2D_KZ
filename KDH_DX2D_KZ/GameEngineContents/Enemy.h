#pragma once
#include "Character.h"
#include <GameEngineCore/GameEngineState.h>

enum class FSM_EnemyState
{
	Idle,
	Chase,
	Attack,
	Death,
	Default,
};

enum class EnemyType
{
	NormalGangster,
	ColoredGangster,
	Cop,
	ShieldCop,
	ShotGunCop,
	Default,
};

enum class EnemyState
{
	Idle,
	Run,
	Attack,
	Dash,
	Death,
	Turn,
	Default,
};

enum class EEnemyState_Emotion
{
	Question,
	NormalExclamation,
	HardExclamation,
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

	void SetEnemyData(EnemyType _EnemyType);
	void InitEnemyData();

	void ChangeEmotion(EEnemyState_Emotion _NextEmotion);
	void UpdateEmotion(float _Delta);



	void ChangeState(EnemyState State);
	void StateUpdate(float _Delta);

	void DirCheck();

	void ChangeAnimationState(std::string_view _StateName);

	void TurnStart();
	void TurnUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	std::shared_ptr<GameEngineSpriteRenderer> GetMainRenderer() const
	{
		return EnemyMainRenderer;
	}

	std::shared_ptr<GameEngineCollision> GetMainCollision() const
	{
		return EnemyMainCollision;
	}

	float4 PlayerChasePos = float4::ZERO;


	// 새로운 FSM 적용
	GameEngineState FSM_EnemyState;

	bool IsEnemyDeath = false;

protected:
	void Start() override;
	void Update(float _Delta) override;

	EnemyState State = EnemyState::Default;
	EnemyDir Dir = EnemyDir::Right;
	EnemyType Type = EnemyType::Default;

	EEnemyState_Emotion EmotionState = EEnemyState_Emotion::Default;

	std::string CurState = "";

private:
	void FSM_Enemy_Idle();
	void FSM_Enemy_Chase();
	void FSM_Enemy_Death();
	void FSM_Enemy_Attack();


	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> EnemyMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> EnemyEffectRenderer;

	std::shared_ptr<class GameEngineSpriteRenderer> EnemyEmotionRenderer;
	std::shared_ptr<class GameEngineCollision> EnemyMainCollision;
	std::shared_ptr<class GameEngineCollision> EnemyDetectCollision;

	void EnemyDamagedEvent();
	void EnemyDetectEvent();

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