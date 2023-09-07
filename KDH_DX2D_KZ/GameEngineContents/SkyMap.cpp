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

		GameEngineTexture::Load(FilePath.PlusFilePath("spr_skyline_clouds.png"));
		GameEngineSprite::CreateSingle("spr_skyline_clouds.png");

	}


	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(1);
		Renderer->SetSprite("spr_skyline_clouds.png");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("spr_skyline_clouds.png");

		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;

		Renderer->Transform.SetLocalPosition(HScale);
	}
}
