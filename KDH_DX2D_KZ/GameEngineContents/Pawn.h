#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 충돌이 가능하며 데미지를 입을 수 있는 오브젝트
class Pawn : public GameEngineActor
{
public:
	Pawn();
	~Pawn();

	Pawn(const Pawn& _Other) = delete;
	Pawn(Pawn&& _Other) noexcept = delete;
	Pawn& operator=(const Pawn& _Other) = delete;
	Pawn& operator=(Pawn&& _Other) noexcept = delete;

	void SetMapTexture(std::string_view _MapTextureName);
	GameEngineColor GetMapColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });
	std::shared_ptr<class GameEngineTexture> MapTexture = nullptr;
protected:

	virtual void SetInitStat();

	virtual void OnDamaged(int _iAttackPower);


private:


};

