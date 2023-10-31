#pragma once

enum class BossLaserType
{
	Normal,
	Rot,
	Default
};

class BossLaser : public GameEngineActor
{
public:
	// constrcuter destructer
	BossLaser();
	~BossLaser();

	// delete Function
	BossLaser(const BossLaser& _Other) = delete;
	BossLaser(BossLaser&& _Other) noexcept = delete;
	BossLaser& operator=(const BossLaser& _Other) = delete;
	BossLaser& operator=(BossLaser&& _Other) noexcept = delete;

	void InitBossLaserData(BossLaserType _Type, float4 _LaserDir, float4 _BulletDir);

	BossLaserType Type;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> BossLaserCollision;
	std::shared_ptr<class GameEngineSpriteRenderer> BossLaserRenderer;

	float4 Dir = float4::ZERO;
	float4 LaserFirePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;
	float Speed = 100.0f;
};
