#pragma once
#include "InteractableObject.h"
#include "Enemy.h"

enum class EDoorType
{
	Normal,
	Iron,
	Default
};

enum class DoorDir
{
	Left,
	Right,
	Default
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

	DoorDir Dir = DoorDir::Left;
	
	
	void SetDoorData(EDoorType _Type, DoorDir _Dir);

	std::shared_ptr<class GameEngineSpriteRenderer> GetMainRenderer() const
	{
		return DoorMainRenderer;
	}

	void ResetDoorState();


	std::vector<Enemy*> DetectedEnemy;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DoorMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> DoorGlowRenderer;

	std::shared_ptr<class GameEngineCollision> DoorMainCollision;

	void DoorAutoOpenEvent();
	void DoorAttackOpenEvent();
	void DoorDetectEnemyEvent();
	
	float DoorPushTimer = 0.f;


};

