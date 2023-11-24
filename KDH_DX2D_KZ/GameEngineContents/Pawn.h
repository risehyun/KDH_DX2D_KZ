#pragma once
#include <GameEngineCore/GameEngineActor.h>


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

	bool IsRecordPlayMode = false;

protected:
	void RecordPlayModeOn();
	void RecordPlayModeOff();

	void Reverse(float _Delta);

	void Replay();

	void UpdateAddingRecordData(float _Delta);

	void AddRecordingRenderer(std::shared_ptr<GameEngineSpriteRenderer> _Renderer)
	{
		RecordingRenderers.push_back(_Renderer);
	}

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> RecordingRenderers;

	std::list<ReverseActorInfo> ActorInfo;
	std::list<ReverseRendererInfo> RendererInfo;
	std::vector<LastAniInfo> LastAniInfos;

	float TimeLimit = 2.0f;


private:


};

