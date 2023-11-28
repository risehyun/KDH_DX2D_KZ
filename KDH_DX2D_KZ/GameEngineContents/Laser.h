#pragma once
#include "InteractableObject.h"

class Laser : public InteractableObject
{
public:
	// constrcuter destructer
	Laser();
	~Laser();

	// delete Function
	Laser(const Laser& _Other) = delete;
	Laser(Laser&& _Other) noexcept = delete;
	Laser& operator=(const Laser& _Other) = delete;
	Laser& operator=(Laser&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> LaserMainRenderer;

	void InitLaserData(bool _UseLongType = false);

	void SetUseLongType()
	{
		IsLongType = true;
	}

	float4 MoveDir = { 1.0f, 0.0f };

	float4 ResetPos = float4::ZERO;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	bool IsLongType = false;

	std::shared_ptr<class GameEngineSpriteRenderer> LaserCeilingRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> LaserAuraRenderer;

	void LaserDetectPlayerEvent();
	void LaserDetectEnemyEvent();
};

