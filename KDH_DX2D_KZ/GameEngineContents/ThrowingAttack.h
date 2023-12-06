#pragma once
#include "Item.h"
#include "Pawn.h"

enum class AttackType
{
	Knife,
	Default,
};

class ThrowingAttack : public Pawn
{
public:
	// constrcuter destructer
	ThrowingAttack();
	~ThrowingAttack();

	// delete Function
	ThrowingAttack(const ThrowingAttack& _Other) = delete;
	ThrowingAttack(ThrowingAttack&& _Other) noexcept = delete;
	ThrowingAttack& operator=(const ThrowingAttack& _Other) = delete;
	ThrowingAttack& operator=(ThrowingAttack&& _Other) noexcept = delete;

//	void InitThrowingAttackData(float4 _ThrowingAttackDir, float _DurationTime);
	void EnemyAttackEvent();

	std::shared_ptr<class GameEngineSpriteRenderer> GetMainRenderer() const
	{
		return ThrowingAttackRenderer;
	}

	void SetDir(float4 _Dir)
	{
		ThrowingAttackDir = _Dir;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineCollision> ThrowingAttackCollision;
	std::shared_ptr<class GameEngineSpriteRenderer> ThrowingAttackRenderer;

private:
	float4 ThrowingAttackDir = float4::ZERO;
	float Speed = 600.0f;
	float DurationTime = 0.0f;

	float4 NextPos = float4::ZERO;

	std::string_view AttackName;

};

