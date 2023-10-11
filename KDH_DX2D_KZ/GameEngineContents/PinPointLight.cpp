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

		// 움직임 범위는 -70(최초,오른쪽 방향 최대값) ~ 110(왼쪽 방향 최대값) 
		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, -70.0f });
	}

}

void PinPointLight::Update(float _Delta)
{
	// 왼쪽 방향 최대값에 도달하기 전이면 isMax를 활성화 (회전 허용)
	if (Renderer->Transform.GetLocalRotationEuler().Z > -120.0f)
	{
		isMoving = true;
	}
	else
	{
		isMoving = false;
	}

	// 왼쪽 방향으로 회전)
	if (true == isMoving)
	{
		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 10.0f * _Delta * -Speed });
	}

	//else if (false == isMoving && Renderer->Transform.GetLocalRotationEuler().Z < -10.0f)
	//{
	//	Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 20.0f * _Delta * Speed });

	//}


	//if (false == isMax)
	//{
	//	// 왼쪽으로 이동
	//	if (Renderer->Transform.GetLocalRotationEuler().Z > -120.0f)
	//	{
	//		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 10.0f * _Delta * -Speed });
	//	}

	//}

	//else
	//{
	//	if (Renderer->Transform.GetLocalRotationEuler().Z < -60.0f)
	//	{
	//		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 10.0f * _Delta * Speed });
	//	}
	//}

}