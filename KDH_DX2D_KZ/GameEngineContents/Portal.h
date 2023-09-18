#pragma once
#include "InteractableObject.h"

class Portal : public InteractableObject
{
public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

	void InitPortalData(std::string_view _NextLevelName, bool _IsUsingInput);
	


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::string NextLevelName;
	bool IsUsingInput;

	std::shared_ptr<class GameEngineSpriteRenderer> InputRenderer;


};

