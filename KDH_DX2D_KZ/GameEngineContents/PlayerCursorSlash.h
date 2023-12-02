#pragma once

class PlayerCursorSlash : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerCursorSlash();
	~PlayerCursorSlash();

	// delete Function
	PlayerCursorSlash(const PlayerCursorSlash& _Other) = delete;
	PlayerCursorSlash(PlayerCursorSlash&& _Other) noexcept = delete;
	PlayerCursorSlash& operator=(const PlayerCursorSlash& _Other) = delete;
	PlayerCursorSlash& operator=(PlayerCursorSlash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerCursorSlashRenderer;

	float4 SlashRot = float4::ZERO;
	
	float Speed = 600.0f;
};