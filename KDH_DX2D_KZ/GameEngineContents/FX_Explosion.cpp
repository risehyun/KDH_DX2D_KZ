#include "PreCompile.h"
#include "FX_Explosion.h"

FX_Explosion::FX_Explosion()
{
}

FX_Explosion::~FX_Explosion()
{
}

void FX_Explosion::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\FX\\ObjFX\\");

		if (nullptr == GameEngineSound::FindSound("sound_explosion1.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_explosion1.wav"));
		}
	}


	FX_ExplosionRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	FX_ExplosionRenderer->CreateAnimation("Explosion", "spr_explosion_1", 0.1f, 0, 10, false);
	FX_ExplosionRenderer->AutoSpriteSizeOn();
	FX_ExplosionRenderer->ChangeAnimation("Explosion");

//	ExplosionFxPlayer = GameEngineSound::SoundPlay("sound_explosion1.wav");
}

void FX_Explosion::Update(float _Delta)
{
	if (FX_ExplosionRenderer->IsCurAnimationEnd())
	{	
		Death();
	}
}