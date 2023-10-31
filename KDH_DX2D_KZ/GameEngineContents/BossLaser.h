#pragma once

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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> BossLaserCollision;
	std::shared_ptr<class GameEngineSpriteRenderer> BossLaserRenderer;
};
