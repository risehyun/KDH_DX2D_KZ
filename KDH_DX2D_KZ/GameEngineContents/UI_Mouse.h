#pragma once

class UI_Mouse : public GameEngineActor
{
public:
	UI_Mouse();
	~UI_Mouse();

	UI_Mouse(const UI_Mouse& _Other) = delete;
	UI_Mouse(UI_Mouse&& _Other) noexcept = delete;
	UI_Mouse& operator=(const UI_Mouse& _Other) = delete;
	UI_Mouse& operator=(UI_Mouse&& _Other) noexcept = delete;

	float4 GetMouseWorldToActorPos()
	{
		return MouseWorldToActorPos;
	}


	float4 GetMouseWorldPositionToActor();


	static UI_Mouse* Mouse;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> MouseRenderer;

	float4 MouseWorldToActorPos = float4::ZERO;

};