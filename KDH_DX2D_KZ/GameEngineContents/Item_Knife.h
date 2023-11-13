#pragma once
#include "InteractableObject.h"

enum class ItemType
{
	Knife,
	Default
};

class Item_Knife : public InteractableObject
{
public:
	// constrcuter destructer
	Item_Knife();
	~Item_Knife();

	// delete Function
	Item_Knife(const Item_Knife& _Other) = delete;
	Item_Knife(Item_Knife&& _Other) noexcept = delete;
	Item_Knife& operator=(const Item_Knife& _Other) = delete;
	Item_Knife& operator=(Item_Knife&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	void MovingArrow(float _Delta);
	void GetItemEvent();

	std::shared_ptr<class GameEngineSpriteRenderer> KnifeMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> PickUpArrowMainRenderer;

	float Speed = 300.0f;
	float ArrowMoveTimer = 0.0f;

	float4 Velocity = float4::ZERO;
	float4 MovePos = float4::UP;

};

