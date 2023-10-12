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
//		WallHoleRenderer->SetSprite("spr_prison_wallhole_alpha.png");
		WallHoleRenderer->AutoSpriteSizeOn();
		WallHoleRenderer->CreateAnimation("WallHole", "spr_prison_wallexplode");

		WallHoleRenderer->ChangeAnimation("WallHole");


		WallHoleRenderer->AutoSpriteSizeOn();
		WallHoleRenderer->On();

	}
}

void WallHole::Update(float _Delta)
{
}
