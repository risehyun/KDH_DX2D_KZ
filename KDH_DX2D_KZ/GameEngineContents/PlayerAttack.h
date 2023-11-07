#pragma once

class PlayerAttack : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerAttack();
	~PlayerAttack();

	// delete Function
	PlayerAttack(const PlayerAttack& _Other) = delete;
	PlayerAttack(PlayerAttack&& _Other) noexcept = delete;
	PlayerAttack& operator=(const PlayerAttack& _Other) = delete;
	PlayerAttack& operator=(PlayerAttack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void BossParryEvent();

private:

	std::shared_ptr<class GameEngineCollision> PlayerAttackCollision;
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerAttackRenderer;

};