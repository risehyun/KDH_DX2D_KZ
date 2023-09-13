#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

private:
	void MakeRain();
};

