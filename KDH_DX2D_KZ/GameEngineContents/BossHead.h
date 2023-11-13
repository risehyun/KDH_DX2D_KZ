#pragma once
#include "Character.h"

class BossHead : public Character
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

	float4 Velocity;

	// y값은 반전되므로 주의할 것
	float4 LeftCheck = { -10.0f, 0.0f };
	float4 RightCheck = { 10.0f, 0.0f };
	float4 UpCheck = { 0.f, 10.0f };
	float4 DownCheck = { 0.f, -10.0f };

	////////////////////// DebugValue
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Left;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Right;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Up;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderer_Down;
};

