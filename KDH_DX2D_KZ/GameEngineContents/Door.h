#pragma once
#include "InteractableObject.h"

enum class EDoorType
{
	Normal,
	Iron,
	Default,
};

class Door : public InteractableObject
{
public:
	// constrcuter destructer
	Door();
	~Door();

	// delete Function
	Door(const Door& _Other) = delete;
	Door(Door&& _Other) noexcept = delete;
	Door& operator=(const Door& _Other) = delete;
	Door& operator=(Door&& _Other) noexcept = delete;

	EDoorType Type;
	
	void SetDoorType(EDoorType _Type);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DoorMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> DoorGlowRenderer;

	std::shared_ptr<class GameEngineCollision> DoorMainCollision;

	void DoorAutoOpenEvent();
	void DoorAttackOpenEvent();
	
	float DoorPushTimer = 0.f;
};

