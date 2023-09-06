#pragma once
#include "Pawn.h"

class Character : public Pawn
{
public:
	Character();
	~Character();

	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;


	void Gravity(float _Delta);

	void GravityReset()
	{
		GravityVector = float4::ZERO;
	}

	float4 GetGravityVector()
	{
		// GravityVector.y > 0.0f
		return GravityVector;
	}

	void GravityOff()
	{
		IsGravity = false;
	}

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}




	float4 ActorCameraPos();

	bool IsGravity = true;

	float GravityPower = 1000.0f;
	float4 GravityVector = float4::ZERO;
};

