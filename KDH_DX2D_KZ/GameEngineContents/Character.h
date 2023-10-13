#pragma once
#include "PreCompile.h"
#include "Pawn.h"

enum class CharacterType
{
	Player,
	NormalEnemy,
	ObjectEnemy,
	Default,
};

class ReverseActorInfo
{
public:
	float Time;
	float4 Pos;
	std::string_view SpriteName;
	int Frame;
};

class ReverseRendererInfo
{
public:
	float Time;
	int RendererIndex = -1; // 몇 번째 렌더러인지
	std::string_view SpriteName;
	int Frame;
};

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
		GravityPower = 200.0f;
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

	void SetCharacterType(CharacterType _CharacterType)
	{
		CharType = _CharacterType;
	}

	bool GetGroundPixelCollision();

	float4 ActorCameraPos();

	CharacterType CharType = CharacterType::Default;

protected:
	bool IsReverse = false;

	void Reverse();
	void ReverseUpdate(float _Delta);

	bool IsGravity = true;
	bool IsGroundPixelCollision = false;

	float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };
	float GravityPower = 200.0f;
	float4 GravityVector = float4::ZERO;

	void AddRenderer(std::shared_ptr<GameEngineSpriteRenderer> _Renderer)
	{
		Renderers.push_back(_Renderer);
	}

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Renderers;

	std::list<ReverseActorInfo> ActorInfo;
	std::list<ReverseRendererInfo> RendererInfo;

private:


};

