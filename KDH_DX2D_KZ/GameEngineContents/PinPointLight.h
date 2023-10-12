#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ERotationDir
{
	Left,
	Right,
	Default,
};


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

	void InitRotationDir(ERotationDir _Dir);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	ERotationDir Dir;

	void RotateLight(float _Delta);
	void DetectEvent(float _Delta);

	float4 MoveDir = float4::ZERO;
	float Speed = 30.0f;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer;
	std::shared_ptr<GameEngineCollision> DetectCollision;
};