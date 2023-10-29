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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	bool IsLongType = false;

	float4 MoveDir = float4::ZERO;

	std::shared_ptr<class GameEngineSpriteRenderer> LaserCeilingRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> LaserAuraRenderer;

	void LaserDetectEnemyEvent();
};

