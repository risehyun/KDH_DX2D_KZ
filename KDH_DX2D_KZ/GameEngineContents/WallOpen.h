#pragma once
#include <GameEngineCore/GameEngineActor.h>

class WallOpen : public GameEngineActor
{
public:
	// constrcuter destructer
	WallOpen();
	~WallOpen();

	// delete Function
	WallOpen(const WallOpen& _Other) = delete;
	WallOpen(WallOpen&& _Other) noexcept = delete;
	WallOpen& operator=(const WallOpen& _Other) = delete;
	WallOpen& operator=(WallOpen&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> WallOpenRenderer;
	bool IsCreateTurret = false;

};

