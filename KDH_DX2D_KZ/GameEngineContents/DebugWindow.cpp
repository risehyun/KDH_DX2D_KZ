#include "PreCompile.h"
#include "DebugWindow.h"
#include "Player.h"
#include "Boss.h"
#include "UI_Mouse.h"
#include "GameStateManager.h"

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
	std::string PlayerWorldPos = Player::MainPlayer->Transform.GetWorldPosition().ToString();
//	UI_Mouse::Mouse->GetMouseWorldToActorPos

	float t = Player::MainPlayer->GetCurrentDashCoolTime();
	std::string CoolTimeDebugValue = std::to_string(t);

	
	ImGui::Text("<Current Player World Position>");
	ImGui::Text(PlayerWorldPos.c_str());

	//int hp = Boss::Boss_HeadHunter->GetBossHp();

	//ImGui::Text("<Boss Current HP>");
	//ImGui::Text(std::to_string(hp).c_str());

	ImGui::Text("<Mouse Screen Position>");
	ImGui::Text(MousePos.c_str());

	ImGui::Text("<CurPlayerDashCoolTime>");
	ImGui::Text(CoolTimeDebugValue.c_str());


	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	int a = GameStateManager::GameState->LeftEnemy;

	ImGui::Text("<LEFT ENEMY COUNT>");
	ImGui::Text(std::to_string(a).c_str());


	
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
