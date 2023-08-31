#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

class GameEngineFrameAnimation
{
	friend class GameEngineSpriteRenderer;

	std::string AnimationName;
	std::string SpriteName;

	std::shared_ptr<GameEngineSprite> Sprite;

	float Inter;
	bool Loop;

	unsigned int Start;
	unsigned int End;
	unsigned int CurIndex;
	float CurTime = 0.0f;
	std::vector<int> Index;

	void Reset();

	SpriteData Update(float _DeltaTime);

};

// 설명 :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
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

	void ChangeAnimation(std::string_view _AnimationName);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	inline void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

protected:
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	int Index = 0;

private:
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;

	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;

	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;

	bool IsImageSize = false;
	float AutoScaleRatio = 1.0f;
};

