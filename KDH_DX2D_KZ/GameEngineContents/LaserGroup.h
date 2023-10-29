#pragma once
#include "Laser.h"

class LaserGroup : public Laser
{
public:
	LaserGroup();
	~LaserGroup();

	// delete Function
	LaserGroup(const LaserGroup& _Other) = delete;
	LaserGroup(LaserGroup&& _Other) noexcept = delete;
	LaserGroup& operator=(const LaserGroup& _Other) = delete;
	LaserGroup& operator=(LaserGroup&& _Other) noexcept = delete;

	void InitLaserGroupData(int _LaserCount, float4 _InitPos, float _XDistance);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	std::vector<std::shared_ptr<Laser>> AllLaser;

	bool IsLongType = false;
	bool IsUseMoving = false;

	float4 MoveDir = float4::ZERO;
};

