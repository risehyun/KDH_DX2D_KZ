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

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> LaserCeilingRenderer;
	void LaserDetectEnemyEvent();
};

