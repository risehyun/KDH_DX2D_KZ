#pragma once
#include "Fx.h"

enum class EFX_DustCloudGroup_Type
{
	RunCloud,
	RollCloud,
	Default,
};

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

	void SetType(EFX_DustCloudGroup_Type _Type);

	EFX_DustCloudGroup_Type Type = EFX_DustCloudGroup_Type::Default;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	void CreateRunCloudGroup();
	void CreateRollCloudGroup();

	float4 PlayerPos = float4::ZERO;
	float4 PlayerDir = float4::ZERO;

	bool IsStartRollCloudMove = false;

	std::vector<std::shared_ptr<Fx>> DustCloudGroup;
	 
};