#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		MainSpriteRenderer->CreateAnimation("Idle", "spr_dragon_idle");
		MainSpriteRenderer->ChangeAnimation("Idle");
		MainSpriteRenderer->Transform.SetLocalPosition({ 100.0f, 0.0f, 0.0f });

		MainSpriteRenderer->Transform.SetLocalScale({36 * 2.2f, 40 * 2.2f});
	//	MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(0.4f);
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void Player::Update(float _Delta)
{
	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}

	GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GrivityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	else 
	{
		GrivityForce = 0.0f;
	}

	// float4 Color = GetColor(Transform.GetWorldPosition());
}