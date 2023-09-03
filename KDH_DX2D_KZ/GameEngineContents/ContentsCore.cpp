#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "MainLevel1_1.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
//	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MainLevel1_1>("MainLevel1_1");
	GameEngineCore::ChangeLevel("TitleLevel");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}