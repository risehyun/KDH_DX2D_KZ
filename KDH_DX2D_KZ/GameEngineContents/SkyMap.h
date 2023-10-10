#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ESkyType
{
	CitySky,
	PrisonSky,
	Defalut,
};

class SkyMap : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyMap();
	~SkyMap();

	// delete Function
	SkyMap(const SkyMap& _Other) = delete;
	SkyMap(SkyMap&& _Other) noexcept = delete;
	SkyMap& operator=(const SkyMap& _Other) = delete;
	SkyMap& operator=(SkyMap&& _Other) noexcept = delete;

	ESkyType Type = ESkyType::Defalut;

	void SetSkyMapType(ESkyType _Type);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float Speed = 100.0f;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
};

