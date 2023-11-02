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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> BossBulletCollision;
	std::shared_ptr<class GameEngineSpriteRenderer> BossBulletRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> BossBulletAreaRenderer;

	float4 Dir = float4::ZERO;
	float4 LaserFirePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;
	float Speed = 100.0f;

	float4 LeftCheck = { -30.0f, 0.0f };
	float4 RightCheck = { 30.0f, 0.0f };
	float4 UpCheck = { 0.f, 30.0f };
	float4 DownCheck = { 0.f, -50.0f };


	float4 MovePos = float4::ZERO;

	bool IsOnCurve = false;
};

