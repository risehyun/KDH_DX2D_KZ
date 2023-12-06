#pragma once
#include "InteractableObject.h"

enum class EItemType  // 아이템 유형
{
	Knife,
	Beer,
	ExplosiveVial,
	Default,
};

class Item : public InteractableObject
{
public:


	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;


	EItemType ItemType = EItemType::Default;

	std::string_view ItemSpriteName;

	void SetItemData(EItemType _ItemType);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	void SetItemSlot();

	void ItemDrop(float _Delta);

	void CollisonEvent_DetectPlayer();
	void MovingPickUpArrow(float _Delta);


	std::shared_ptr<class GameEngineSpriteRenderer> ItemMainRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> PickUpArrowMainRenderer;

	float Speed = 300.0f;
	float ArrowMoveTimer = 0.0f;

	float4 Velocity = float4::ZERO;
	float4 MovePos = float4::UP;
};