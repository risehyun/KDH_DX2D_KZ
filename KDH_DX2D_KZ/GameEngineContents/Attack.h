#pragma once

// ★ Bullet이 이 클래스를 상속받도록
class Attack : public GameEngineActor
{
public:
	// constrcuter destructer
	Attack();
	~Attack();

	// delete Function
	Attack(const Attack& _Other) = delete;
	Attack(Attack&& _Other) noexcept = delete;
	Attack& operator=(const Attack& _Other) = delete;
	Attack& operator=(Attack&& _Other) noexcept = delete;

	void InitAttackData(ContentsCollisionType _Type, float4 _AttackDir, float _DurationTime, bool _IsUsingAutoDeath = true);

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineCollision> AttackCollision;
	std::shared_ptr<class GameEngineSpriteRenderer> AttackRenderer;

private:
	float4 AttackDir = float4::ZERO;
	float DurationTime = 0.0f;
	bool IsUsingAutoDeath = false;
};

