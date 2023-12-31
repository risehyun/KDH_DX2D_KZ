#include "PreCompile.h"
#include "GameEngineMesh.h"

GameEngineMesh::GameEngineMesh()
{
}

GameEngineMesh::~GameEngineMesh()
{
}

void GameEngineMesh::InputAssembler1()
{
	if (nullptr == VertexBufferPtr)
	{
		MsgBoxAssert("매쉬가 세팅되어 있지 않습니다.");
		return;
	}

	VertexBufferPtr->Setting();

	GameEngineCore::GetContext()->IASetPrimitiveTopology(TOPOLOGY);
}

void GameEngineMesh::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgBoxAssert("매쉬가 세팅되어 있지 않습니다.");
		return;
	}

	IndexBufferPtr->Setting();
}

void GameEngineMesh::Draw()
{
	GameEngineCore::GetContext()->DrawIndexed(IndexBufferPtr->GetIndexCount(), 0, 0);
}