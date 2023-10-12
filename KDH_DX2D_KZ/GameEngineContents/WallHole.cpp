#include "PreCompile.h"
#include "WallHole.h"

WallHole::WallHole()
{
}

WallHole::~WallHole()
{
}

void WallHole::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Object\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_prison_wallhole_alpha.png"));
			GameEngineSprite::CreateSingle("spr_prison_wallhole_alpha.png");
		}

		WallHoleRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));
		WallHoleRenderer->AutoSpriteSizeOn();
		WallHoleRenderer->CreateAnimation("WallHole", "spr_prison_wallexplode", 0.2f, 0, 5, false);
		WallHoleRenderer->ChangeAnimation("WallHole");

	}


	WallHoleParticleRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));
	WallHoleParticleRenderer->AutoSpriteSizeOn();
	WallHoleParticleRenderer->Transform.SetLocalPosition({0.0f, -10.0f, 1.0f});
	WallHoleParticleRenderer->CreateAnimation("WallExplode", "spr_prison_wallexplode_particles", 0.1f, 0, 20, false);
	WallHoleParticleRenderer->ChangeAnimation("WallExplode");

}

void WallHole::Update(float _Delta)
{
}
