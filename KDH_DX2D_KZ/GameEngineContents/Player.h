#pragma once
#include "Character.h"

// Ό³Έν :
class Player : public Character
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


	void CameraFocus();


	float4 ActorCameraPos()
	{
		return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	}

	static Player* MainPlayer;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;
	float4 GravityForce = {0.0f, 0.0f, 0.0f, 1.0f};



	////////////////////// DebugValue
	float4 LeftCheck = { 0.5f, 0.0f };
	float4 RightCheck = { 0.5f, 0.0f };
	float4 UpCheck = { 0.0f, -50.0f };
	float4 DownCheck = { 0.0f, 50.0f };
};

