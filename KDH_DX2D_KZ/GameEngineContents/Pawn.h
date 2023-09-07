#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �浹�� �����ϸ� �������� ���� �� �ִ� ������Ʈ
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

protected:




	GameEngineColor GetMapColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });


	virtual void SetInitStat();

	virtual void OnDamaged(int _iAttackPower);

	std::shared_ptr<class GameEngineTexture> MapTexture = nullptr;
private:


};
