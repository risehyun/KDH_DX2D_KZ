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

	// float Inter;
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

public:
	std::vector<float> Inter;
};

enum class PivotType
{
	Center,
	Bottom,
	Left,
	LeftTop,
};

struct SpriteRendererInfo
{
	int FlipLeft = 0;
	int FlipUp = 0;
	float Temp1;
	float Temp2;
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

	// 현재 재생중인 애니메이션이 있는 경우 강제로 애니메이션 정지
	void SetSprite(std::string_view _Name, unsigned int index = 0);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f,
		unsigned int _Start = -1,
		unsigned int _End = -1,
		bool _Loop = true
	);

	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false, unsigned int _FrameIndex = 0);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	inline void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio.X = _Ratio;
		AutoScaleRatio.Y = _Ratio;
	}

	inline void SetAutoScaleRatio(float4 _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

	bool IsRight()
	{
		return 0 < AutoScaleRatio.X;
	}

	void RightFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 0;
	}

	void LeftFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 1;
	}

	void UpFlip()
	{
		SpriteRendererInfoValue.FlipUp = 1;
	}

	void DownFlip()
	{
		SpriteRendererInfoValue.FlipUp = 0;
	}

	bool IsCurAnimationEnd()
	{
		return CurFrameAnimations->IsEnd;
	}

	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return CurFrameAnimations->AnimationName == _AnimationName;
	}

	std::shared_ptr<GameEngineFrameAnimation> FindAnimation(std::string_view _AnimationName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

		if (false == FrameAnimations.contains(UpperName))
		{
			return nullptr;
		}

		return FrameAnimations[UpperName];
	}

	void AnimationPauseSwitch();
	void AnimationPauseOn();
	void AnimationPauseOff();

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function);

	void SetPivotValue(const float4& _Value)
	{
		Pivot = _Value;
	}
	void SetPivotType(PivotType _Type);
	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);

	std::shared_ptr<GameEngineSprite> GetSprite()
	{
		return Sprite;
	}

	const SpriteData& GetCurSprite()
	{
		return CurSprite;
	}

	inline unsigned int GetCurIndex() const
	{
		return CurFrameAnimations->CurIndex;
	}

	inline GameEngineTransform& GetImageTransform()
	{
		return ImageTransform;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	int Index = 0;

private:
	// 부모인 actor를 기준으로한

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;

	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;

	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;
	SpriteRendererInfo SpriteRendererInfoValue;

	std::shared_ptr<class GameEngineSampler> Sampler;

	bool IsImageSize = false;
	float4 AutoScaleRatio = { 1.0f,1.0f,1.0f };
	bool IsPause = false;

	float4 Pivot = { 0.5f, 0.5f };

	GameEngineTransform ImageTransform;
};

