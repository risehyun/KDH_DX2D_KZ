#pragma once
#include "Fx.h"

class Fx_BossSmokeGroup : public Fx
{
public:
	// constrcuter destructer
	Fx_BossSmokeGroup();
	~Fx_BossSmokeGroup();

	// delete Function
	Fx_BossSmokeGroup(const Fx_BossSmokeGroup& _Other) = delete;
	Fx_BossSmokeGroup(Fx_BossSmokeGroup&& _Other) noexcept = delete;
	Fx_BossSmokeGroup& operator=(const Fx_BossSmokeGroup& _Other) = delete;
	Fx_BossSmokeGroup& operator=(Fx_BossSmokeGroup&& _Other) noexcept = delete;

	void CreateSmokeGroup(float4 _InitFxPos);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float4 InitFxPos = float4::ZERO;
};


