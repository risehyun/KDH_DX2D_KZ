#include "PreCompile.h"
#include "Map.h"
#include "ContentsDefine.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
//	Transform.SetLocalPosition({ WINDOW_SIZE_HALF });
}

void Map::Update(float _Delta)
{
}

void Map::InitMap(std::string_view _MapName, const float _Scale, const float4& _Pos)
{
	MapName = _MapName;

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
	{
		GameEngineTexture::Load(FilePath.PlusFilePath(_MapName));
		GameEngineSprite::CreateSingle(_MapName);

		int a = 0;
	}

	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	MapRenderer->SetSprite(_MapName);

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find(_MapName);

	float4 HScale = MapTexture->GetScale().Half();
	HScale.Y *= -1.0f;

	MapRenderer->Transform.SetLocalPosition(HScale);

}

void Map::InitDebuggedMap(std::string_view _MapName, std::string_view _DebugMapName)
{
}

void Map::SwitchingRender()
{
}
