#pragma once
#include "Pawn.h"
class BossBullet : public Pawn
{
public:
	// constrcuter destructer
	BossBullet();
	~BossBullet();

	// delete Function
	BossBullet(const BossBullet& _Other) = delete;
	BossBullet(BossBullet&& _Other) noexcept = delete;
	BossBullet& operator=(const BossBullet& _Other) = delete;
	BossBullet& operator=(BossBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> BossBulletCollision;
	std::shared_ptr<class GameEngineSpriteRenderer> BossBulletRenderer;

	float4 Dir = float4::ZERO;
	float4 LaserFirePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;
	float Speed = 100.0f;

	float4 MovePos = float4::ZERO;
};