#include "PreCompile.h"
#include "SkyMap.h"

SkyMap::SkyMap()
{
}

SkyMap::~SkyMap()
{
}

void SkyMap::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("Skyline.png"));
		GameEngineSprite::CreateSingle("Skyline.png");


		GameEngineTexture::Load(FilePath.PlusFilePath("Skyline_2.png"));
		GameEngineSprite::CreateSingle("Skyline_2.png");

	}


	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Skyline);
		Renderer->SetSprite("Skyline_2.png");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Skyline_2.png");

		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;

		Renderer->Transform.SetLocalPosition(HScale);
	}
}

void SkyMap::Update(float _Delta)
{
	if (true == GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition({ -Speed * _Delta, 0.0f });
	}

	else if (true == GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition({ Speed * _Delta, 0.0f });
	}


}

void SkyMap::SetSkyMapType(ESkyType _Type)
{
	Type = _Type;

	if (Type == ESkyType::CitySky)
	{
		Renderer->SetSprite("Skyline.png");
	}

	else if (Type == ESkyType::PrisonSky)
	{
		Renderer->SetSprite("Skyline_2.png");
	}

}
