#pragma once
#include <GameEngineCore/GameEngineActor.h>

class WallHole : public GameEngineActor
{
public:
	// constrcuter destructer
	WallHole();
	~WallHole();

	// delete Function
	WallHole(const WallHole& _Other) = delete;
	WallHole(WallHole&& _Other) noexcept = delete;
	WallHole& operator=(const WallHole& _Other) = delete;
	WallHole& operator=(WallHole&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> WallHoleRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> WallHoleFxRenderer;
};

