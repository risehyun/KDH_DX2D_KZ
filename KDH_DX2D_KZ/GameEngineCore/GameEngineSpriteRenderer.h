#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

class GameEngineFrameAnimation
{
	friend class GameEngineSpriteRenderer;

	GameEngineSpriteRenderer* Parent = nullptr;

	std::string AnimationName;
	std::string SpriteName;

	std::shared_ptr<GameEngineSprite> Sprite = nullptr;

	float Inter;
	bool Loop;
	bool IsEnd;

	bool EventCheck = false;

	unsigned int Start;
	unsigned int End;
	unsigned int CurIndex;
	float CurTime = 0.0f;
	std::vector<int> Index;

	void Reset();

	std::map<int, std::function<void(GameEngineSpriteRenderer*)>> FrameEventFunction;

	std::function<void(GameEngineSpriteRenderer*)> EndEvent;

	SpriteData Update(float _DeltaTime);

	void EventCall(int _Frame);
};

enum class SamplerOption
{
	LINEAR,
	POINT,
};

// 설명 :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
	friend GameEngineFrameAnimation;

public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	// 스프라이트는 기본적으로 
	void SetSprite(std::string_view _Name, unsigned int index = 0);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f,
		unsigned int _Start = -1,
		unsigned int _End = -1,
		bool _Loop = true
	);

	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	inline void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

	void SetSamplerState(SamplerOption _Option);

	bool IsCurAnimationEnd()
	{
		return CurFrameAnimations->IsEnd;
	}

	void AnimationPauseSwitch();
	void AnimationPauseOn();
	void AnimationPauseOff();

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function);

protected:
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	int Index = 0;

private:
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;

	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;

	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;

	std::shared_ptr<class GameEngineSampler> Sampler;
	bool IsImageSize = false;
	float AutoScaleRatio = 1.0f;
	bool IsPause = false;
};

