#include "PreCompile.h"
#include "MainLevel1_1.h"
#include "Player.h"
#include "PlayMap.h"

MainLevel1_1::MainLevel1_1()
{
}

MainLevel1_1::~MainLevel1_1()
{
}

void MainLevel1_1::Start()
{

	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Texture");
		Dir.MoveChild("Map");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

//		GameEngineTexture::Load(Dir.PlusFilePath("Map_MainLevel1.png"));
		GameEngineSprite::CreateSingle("Map_MainLevel1.png");

	}




	//GameEnginePath FilePath;
	//FilePath.SetCurrentPath();
	//FilePath.MoveParentToExistsChild("ContentsResources");
	//FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
	//{
	//	GameEngineTexture::Load(FilePath.PlusFilePath("Map_MainLevel1_1.png"));
	//	GameEngineSprite::CreateSingle("Map_MainLevel1_1.png");
	//}
}

void MainLevel1_1::Update(float _Delta)
{
}

void MainLevel1_1::LevelStart(GameEngineLevel* _PrevLevel)
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
		Object->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y + 300.0f });
	}

	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>();
	}
}

void MainLevel1_1::LevelEnd(GameEngineLevel* _NextLevel)
{
}
