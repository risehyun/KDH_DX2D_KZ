#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineSound.h>

class UI_Title_Background : public GameEngineActor
{
public:
	UI_Title_Background();
	~UI_Title_Background();

	UI_Title_Background(const UI_Title_Background& _Other) = delete;
	UI_Title_Background(UI_Title_Background&& _Other) noexcept = delete;
	UI_Title_Background& operator=(const UI_Title_Background& _Other) = delete;
	UI_Title_Background& operator=(UI_Title_Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;



private:
//	void LevelEnd() override;

	float RainCreateTimer = 0.f;

	std::shared_ptr<GameEngineSpriteRenderer> RainRenderer;

	GameEngineSoundPlayer BGMPlayer;

	void NeonSoundEvent(GameEngineRenderer* _Renderer);
};

