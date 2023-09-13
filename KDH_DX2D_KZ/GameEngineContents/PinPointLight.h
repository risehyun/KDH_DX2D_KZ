#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PinPointLight : public GameEngineActor
{
public:
	// constrcuter destructer
	PinPointLight();
	~PinPointLight();

	// delete Function
	PinPointLight(const PinPointLight& _Other) = delete;
	PinPointLight(PinPointLight&& _Other) noexcept = delete;
	PinPointLight& operator=(const PinPointLight& _Other) = delete;
	PinPointLight& operator=(PinPointLight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float NextRot = 0.f;
	float Speed = 100.0f;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer;
};