#pragma once
#include "Character.h"
#include <GameEngineCore/GameEngineState.h>

enum class FSM_EnemyState
{
	Idle,
	Chase,
	Attack,
	Death,
	Appear,
	Default,
};

enum class EnemyType
{
	NormalGangster,
	ColoredGangster,
	Cop,
	ShieldCop,
	ShotGunCop,
	FloorTurret,
	WallTurret,
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

	void SetEnemyData(EnemyType _EnemyType, EnemyDir _InitDir);
	void InitEnemyData();

	void ChangeEmotion(EEnemyState_Emotion _NextEmotion);

	void DirCheck();

	void ResetDir();



	std::shared_ptr<GameEngineSpriteRenderer> GetMainRenderer() const
	{
		return EnemyMainRenderer;
	}

	std::shared_ptr<GameEngineCollision> GetMainCollision() const
	{
		return EnemyMainCollision;
	}

	float4 GetEnemyDir() const
	{

		if (Dir == EnemyDir::Left)
		{
			return float4::LEFT;
		}

		else if (Dir == EnemyDir::Right)
		{
			return float4::RIGHT;
		}

		else
		{
			return float4::ZERO;
		}

	}

	float4 PlayerChasePos = float4::ZERO;


	// 새로운 FSM 적용
	GameEngineState FSM_EnemyState;

	bool IsEnemyDeath = false;
	bool IsDetectDoor = false;

	float Speed = 200.0f;

	bool IsUsingAutoPattern = false;

	std::shared_ptr<class GameEngineCollision> EnemyMainCollision;
	std::shared_ptr<class GameEngineCollision> EnemyDetectCollision;

protected:
	void Start() override;
	void Update(float _Delta) override;

	EnemyState State = EnemyState::Default;

	EnemyDir InitDir = EnemyDir::Default;
	EnemyDir Dir = EnemyDir::Right;
	EnemyType Type = EnemyType::Default;

	EEnemyState_Emotion EmotionState = EEnemyState_Emotion::Default;

	std::string CurState = "";

private:
	void FSM_Enemy_Idle();
	void FSM_Enemy_Chase();
	void FSM_Enemy_Death();
	void FSM_Enemy_Attack();
	void FSM_Enemy_Appear();


	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> EnemyMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> EnemyEffectRenderer;

	std::shared_ptr<class GameEngineSpriteRenderer> EnemyEmotionRenderer;


	void EnemyDamagedEvent(float _Delta);
	void EnemyPlayerDetectEvent();

	////////////////////// DebugValue
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Left;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Right;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Up;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Down;

	// y값은 반전되므로 주의할 것
	float4 LeftCheck = { -30.0f, -38.0f };
	float4 RightCheck = { 30.0f, 0.0f };
	float4 UpCheck = { 0.f, 30.0f };
	float4 DownCheck = { 0.f, -40.0f };

	float4 AttackFireInitPos = float4::ZERO;
	float4 AttackFireDir = float4::ZERO;

	float4 CheckPos = float4::ZERO;

};