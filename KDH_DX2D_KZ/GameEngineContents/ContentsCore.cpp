#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("PlayLevel");

	// 자기 텍스처 로드해야 한다.

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}