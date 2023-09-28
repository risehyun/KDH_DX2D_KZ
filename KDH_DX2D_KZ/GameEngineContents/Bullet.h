#pragma once

class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	void InitBulletData(ContentsCollisionType _Type, float4 _BulletDir);

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineCollision> BulletCollision;

	std::shared_ptr<class GameEngineSpriteRenderer> BulletRenderer;

private:
	float4 BulletDir = float4::ZERO;




};

