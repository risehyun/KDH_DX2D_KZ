#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;

private:
};

