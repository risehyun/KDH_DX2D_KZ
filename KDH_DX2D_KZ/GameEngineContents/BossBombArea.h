#pragma once
class BossBombArea : public GameEngineActor
{
public:
	// constrcuter destructer
	BossBombArea();
	~BossBombArea();

	// delete Function
	BossBombArea(const BossBombArea& _Other) = delete;
	BossBombArea(BossBombArea&& _Other) noexcept = delete;
	BossBombArea& operator=(const BossBombArea& _Other) = delete;
	BossBombArea& operator=(BossBombArea&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> BossBombAreaRenderer;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineCollision> BossBombAreaCollision;
	void BossBombDamagedEvent();
};

