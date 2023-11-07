#pragma once
#include "Pawn.h"

class BossGrenade : public Pawn
{
public:
	// constrcuter destructer
	BossGrenade();
	~BossGrenade();

	// delete Function
	BossGrenade(const BossGrenade& _Other) = delete;
	BossGrenade(BossGrenade&& _Other) noexcept = delete;
	BossGrenade& operator=(const BossGrenade& _Other) = delete;
	BossGrenade& operator=(BossGrenade&& _Other) noexcept = delete;

	void SetGrenadeSpeed(float _Speed)
	{
		Speed = _Speed;
	}

	void SetGrenadeDir(float4 _InitDir)
	{
		Dir = _InitDir;

		if (float4::LEFT == Dir)
		{
			MovePos = { (float4::LEFT + float4::UP) };
		}
		else if (float4::RIGHT == Dir)
		{
			MovePos = { (float4::RIGHT + float4::UP) };
		}
	}

	bool GetSelfAttackable() const
	{
		return IsSelfAttackable;
	}

	void SetSelfAttackable()
	{
		IsSelfAttackable = true;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> BossGrenadeCollision;
	std::shared_ptr<class GameEngineCollision> BossGrenadeAreaCollision;

	std::shared_ptr<class GameEngineSpriteRenderer> BossGrenadeRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> BossGrenadeAreaRenderer;

	float4 Dir = float4::ZERO;
	float Speed = 100.0f;

	float4 LeftCheck = { -30.0f, 0.0f };
	float4 RightCheck = { 30.0f, 0.0f };
	float4 UpCheck = { 0.f, 30.0f };
	float4 DownCheck = { 0.f, -50.0f };

	float4 MovePos = float4::ZERO;

	float4 pos;
	float4 vel;
	float radius = 10.0f;


	bool IsSelfAttackable = false;
};

