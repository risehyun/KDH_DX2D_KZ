#include "PreCompile.h"
#include "GameEngineDebugCore.h"
#include "GameEngineRenderUnit.h"
#include "GameEngineCamera.h"
#include "GameEngineLevel.h"

class GameEngineDebugInfo
{
public:
	GameEngineCamera* Camera;
	TransformData Data;
	GameEngineRenderUnit Unit;

};

std::vector<GameEngineDebugInfo> DebugUnit;
GameEngineLevel* GameEngineDebug::GameEngineDebugCore::CurLevel = nullptr;


void GameEngineDebug::GameEngineDebugCore::DebugInit()
{
	// �̳༮ ���� 1���� ������ 1�� �׸��� �ִ�.
	DebugUnit.resize(100);
}

void GameEngineDebug::GameEngineDebugCore::DebugRender()
{
	for (size_t i = 0; i < DebugUnit.size(); i++)
	{
		DebugUnit[i].Unit.ResSetting();
		DebugUnit[i].Unit.Draw();
	}

	DebugUnit.clear();
}

void GameEngineDebug::DrawBox2D(const GameEngineTransform& _Trans, GameEngineCamera* _Camera)
{
	GameEngineDebug::DrawBox2D(_Trans.GetWorldScale(), _Trans.GetWorldRotationEuler(), _Trans.GetWorldPosition(), _Camera);
}

void GameEngineDebug::DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, GameEngineCamera* _Camera)
{
	if (nullptr == _Camera)
	{
		_Camera = GameEngineDebug::GameEngineDebugCore::CurLevel->GetMainCamera().get();
	}

	GameEngineDebugInfo& Value = DebugUnit.emplace_back();
	Value.Camera = _Camera;
	Value.Unit.SetMesh("Rect");
	Value.Unit.SetMaterial("2DTextureWire");
}
