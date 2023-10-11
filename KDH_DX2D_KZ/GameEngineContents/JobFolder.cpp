#include "PreCompile.h"
#include "JobFolder.h"

JobFolder::JobFolder()
{
}

JobFolder::~JobFolder()
{
}

void JobFolder::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		JobFolderFrontRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));
		JobFolderFrontRenderer->CreateAnimation("JobFolderFront", "spr_jobfolder_front", 0.1f, 0, 0, true);
		JobFolderFrontRenderer->AutoSpriteSizeOn();
		JobFolderFrontRenderer->ChangeAnimation("JobFolderFront");
		JobFolderFrontRenderer->Off();
	}

	{
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Texture\\Object\\");
			{
				GameEngineTexture::Load(FilePath.PlusFilePath("JobFolderAll.png"));
				GameEngineSprite::CreateSingle("JobFolderAll.png");
			}

			JobFolderAllRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));
			JobFolderAllRenderer->SetSprite("JobFolderAll.png");
			JobFolderAllRenderer->AutoSpriteSizeOn();
			JobFolderAllRenderer->On();

		}
	
		
	}


}

void JobFolder::Update(float _Delta)
{
}
