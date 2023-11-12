#pragma once
#include "Pawn.h"

class BossHead : public Pawn
{
public:
	// constrcuter destructer
	BossHead();
	~BossHead();

	// delete Function
	BossHead(const BossHead& _Other) = delete;
	BossHead(BossHead&& _Other) noexcept = delete;
	BossHead& operator=(const BossHead& _Other) = delete;
	BossHead& operator=(BossHead&& _Other) noexcept = delete;

	void SetDir(float4 _InitDir)
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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BossHeadRenderer;

	float4 Dir = float4::ZERO;
	float4 MovePos = float4::ZERO;

	float Speed = 100.0f;

	float4 pos;
	float4 Velocity;
};

