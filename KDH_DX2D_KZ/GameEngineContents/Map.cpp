#include "PreCompile.h"
#include "Map.h"
#include "ContentsDefine.h"
#include <GameEnginePlatform/GameEngineInput.h>

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
	if (true == GameEngineInput::IsDown('J'))
	{
		SwitchingRender();
	}

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
//	MapRenderer->On();

}

void Map::InitDebuggedMap(std::string_view _MapName, std::string_view _DebugMapName)
{
	MapName = _MapName;
	DebugMapName = _DebugMapName;


	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");

		GameEngineTexture::Load(FilePath.PlusFilePath(_MapName));
		GameEngineSprite::CreateSingle(_MapName);
	}

	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	MapRenderer->SetSprite(_MapName);

	std::shared_ptr<GameEngineTexture> MapTexture = GameEngineTexture::Find(_MapName);

	float4 HScale = MapTexture->GetScale().Half();
	HScale.Y *= -1.0f;

	MapRenderer->Transform.SetLocalPosition(HScale);
	MapRenderer->Off();
	bool temp = MapRenderer->IsUpdate();

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");

		GameEngineTexture::Load(FilePath.PlusFilePath(_DebugMapName));
		GameEngineSprite::CreateSingle(_DebugMapName);

	}

	DebugMapRenderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	DebugMapRenderer->SetSprite(_DebugMapName);

	std::shared_ptr<GameEngineTexture> DebugMapTexture = GameEngineTexture::Find(_DebugMapName);

	float4 HScaleDebug = DebugMapTexture->GetScale().Half();
	HScaleDebug.Y *= -1.0f;

	DebugMapRenderer->Transform.SetLocalPosition(HScaleDebug);
	DebugMapRenderer->Off();




}

void Map::SwitchingRender()
{

	int a = 0;

	/*SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		MapRenderer->On();
		DebugMapRenderer->Off();
	}
	else
	{
		MapRenderer->Off();
		DebugMapRenderer->On();
	}*/
}