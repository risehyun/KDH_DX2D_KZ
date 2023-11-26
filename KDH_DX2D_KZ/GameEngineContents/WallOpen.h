#pragma once
#include "Pawn.h"
#include "Enemy.h"

class WallOpen : public Pawn
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

	void ResetWall();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> WallOpenRenderer;
	bool IsCreateTurret = false;

	std::vector<std::shared_ptr<Enemy>> AllSpawnedEnemy;

};

