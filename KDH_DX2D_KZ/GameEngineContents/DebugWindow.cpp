#include "PreCompile.h"
#include "DebugWindow.h"

DebugWindow* DebugWindow::DebugGUI = nullptr;
DebugWindow::DebugWindow()
{
	DebugGUI = this;
}

DebugWindow::~DebugWindow()
{
}

void DebugWindow::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	CurTab = Tabs[0];
	Tabs.push_back(std::make_shared<TestTab>("Debug"));
}

void TestTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();

	ImGui::Text("<Mouse Screen Position>");
	ImGui::Text(MousePos.c_str());

	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}
}

void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{

}

void DebugWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	for (size_t i = 0; i < Tabs.size(); i++)
	{
		ImGui::SameLine();
		if (ImGui::Button(Tabs[i]->Name.c_str()))
		{
			CurTab = Tabs[i];
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _DeltaTime);
	}


	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}
	}
}

void DebugWindow::LevelChangeScreen(GameEngineLevel* _Level)
{
}