#pragma once

class FX_Explosion : public GameEngineActor
{
	public:
	// constrcuter destructer
	FX_Explosion();
	~FX_Explosion();

	// delete Function
	FX_Explosion(const FX_Explosion& _Other) = delete;
	FX_Explosion(FX_Explosion&& _Other) noexcept = delete;
	FX_Explosion& operator=(const FX_Explosion& _Other) = delete;
	FX_Explosion& operator=(FX_Explosion&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FX_ExplosionRenderer;
	GameEngineSoundPlayer ExplosionFxPlayer;

};

