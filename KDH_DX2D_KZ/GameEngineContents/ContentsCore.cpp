#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "MainLevel1_1.h"
#include "MainLevel2_1.h"
#include "MainLevel2_2.h"
#include "MainLevel2_3.h"
#include "MainLevel2_4.h"
#include "MainLevel2_5.h"
#include "BossLevel1_2.h"
#include "EndingLevel.h"

#include "DebugWindow.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	// Imgui�� �̿��� ����׿� ������ ����
	GameEngineGUI::CreateGUIWindow<DebugWindow>("Debug");

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MainLevel1_1>("MainLevel1_1");
	GameEngineCore::CreateLevel<MainLevel2_1>("MainLevel2_1");
	GameEngineCore::CreateLevel<MainLevel2_2>("MainLevel2_2");
	GameEngineCore::CreateLevel<MainLevel2_3>("MainLevel2_3");
	GameEngineCore::CreateLevel<MainLevel2_4>("MainLevel2_4");
	GameEngineCore::CreateLevel<MainLevel2_5>("MainLevel2_5");
	GameEngineCore::CreateLevel<BossLevel1_2>("BossLevel1_2");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	GameEngineCore::ChangeLevel("BossLevel1_2");

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}