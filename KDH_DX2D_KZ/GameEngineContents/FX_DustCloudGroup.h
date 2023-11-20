#pragma once
#include "Fx.h"




class FX_DustCloudGroup : public Fx
{
public:
	// constrcuter destructer
	FX_DustCloudGroup();
	~FX_DustCloudGroup();

	// delete Function
	FX_DustCloudGroup(const FX_DustCloudGroup& _Other) = delete;
	FX_DustCloudGroup(FX_DustCloudGroup&& _Other) noexcept = delete;
	FX_DustCloudGroup& operator=(const FX_DustCloudGroup& _Other) = delete;
	FX_DustCloudGroup& operator=(FX_DustCloudGroup&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};