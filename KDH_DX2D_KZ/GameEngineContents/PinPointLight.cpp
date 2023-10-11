#include "PreCompile.h"
#include "PinPointLight.h"

PinPointLight::PinPointLight()
{
}

PinPointLight::~PinPointLight()
{
}

void PinPointLight::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Object\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("PinPointLight.png"));
		GameEngineSprite::CreateSingle("PinPointLight.png");

	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
		Renderer->SetSprite("PinPointLight.png");

		Renderer->AutoSpriteSizeOn();

		// 움직임 범위는 -70(최초,오른쪽 방향 최대값) ~ -110(왼쪽 방향 최대값) 
		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, -70.0f });
	}

	{
		MoveDir = { 0.0f, 0.0f, -1.0f };
	}
}

void PinPointLight::Update(float _Delta)
{
	RotateLight(_Delta);
}

void PinPointLight::RotateLight(float _Delta)
{
	Renderer->Transform.AddLocalRotation({ MoveDir * _Delta * Speed });

	if (Renderer->Transform.GetLocalRotationEuler().Z < -110.0f)
	{
		MoveDir = { 0.0f, 0.0f, 1.0f };
	}

	if (Renderer->Transform.GetLocalRotationEuler().Z > -70.0f)
	{
		MoveDir = { 0.0f, 0.0f, -1.0f };
	}
}
