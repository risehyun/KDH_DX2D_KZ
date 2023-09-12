#pragma once
#include <GameEngineCore/GameEngineActor.h>

class InteractableObject : public GameEngineActor
{
public:
	// constrcuter destructer
	InteractableObject();
	~InteractableObject();

	// delete Function
	InteractableObject(const InteractableObject& _Other) = delete;
	InteractableObject(InteractableObject&& _Other) noexcept = delete;
	InteractableObject& operator=(const InteractableObject& _Other) = delete;
	InteractableObject& operator=(InteractableObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineCollision> InteractCollision;

private:

};

