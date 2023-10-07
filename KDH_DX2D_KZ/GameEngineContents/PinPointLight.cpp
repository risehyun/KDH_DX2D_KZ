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

		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 90.0f });
	}

}

void PinPointLight::Update(float _Delta)
{
	// 각도가 120도 이하이면 +10
	if (Renderer->Transform.GetLocalRotationEuler().Z < 120.0f)
	{
		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 10.0f * _Delta });

		//if (Renderer->Transform.GetLocalRotationEuler().Z > 120.0f)
		//{
		//	Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, -10.0f * _Delta });
		//}
	}




}