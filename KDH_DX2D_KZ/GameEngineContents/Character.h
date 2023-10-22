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

class LastAniInfo
{
public:
	std::string AniName;
	int Index = -1;
};

class ReverseActorInfo
{
public:
	float Time;
	float4 Pos;
};

class ReverseRendererInfo
{
public:
	float Time;
	int RendererIndex = -1; // 몇 번째 렌더러인지
	std::string_view SpriteName;
	int Frame;
	int FilpDir;
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

	void ReverseOn();
	void ReverseOff();

	void Reverse();

	float GravityPower = 200.0f;

protected:

	void UpdateAddingReverseData(float _Delta);

	bool IsGravity = true;
	bool IsGroundPixelCollision = false;

	float4 GravityForce = { 0.0f, 0.0f, 0.0f, 1.0f };

	float4 GravityVector = float4::ZERO;

	void AddReverseRenderer(std::shared_ptr<GameEngineSpriteRenderer> _Renderer)
	{
		Renderers.push_back(_Renderer);
	}

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Renderers;

	std::list<ReverseActorInfo> ActorInfo;
	std::list<ReverseRendererInfo> RendererInfo;

private:
	bool IsReverse = false;
	std::vector<LastAniInfo> LastAniInfos;

};

