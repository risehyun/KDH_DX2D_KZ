#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class Tab
{
public:
	std::string Name;
	int Index;

	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;

	Tab(std::string_view _Name)
	{
		Name = _Name;
	}
};

class TestTab : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	TestTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};


class LevelChangeTab : public Tab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	LevelChangeTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};


class DebugWindow : public GameEngineGUIWindow
{
public:
	static DebugWindow* DebugGUI;

	static DebugWindow* GetDebugGUI()
	{
		if (nullptr == DebugGUI)
		{
			MsgBoxAssert("DebugWindow 인스턴스가 존재하지 않습니다.");
		}

		return DebugGUI;
	}

	// constrcuter destructer
	DebugWindow();
	~DebugWindow();

	// delete Function
	DebugWindow(const DebugWindow& _Other) = delete;
	DebugWindow(DebugWindow&& _Other) noexcept = delete;
	DebugWindow& operator=(const DebugWindow& _Other) = delete;
	DebugWindow& operator=(DebugWindow&& _Other) noexcept = delete;


	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	void LevelChangeScreen(GameEngineLevel* _Level);

	std::shared_ptr<Tab> CurTab = nullptr;
	std::vector<std::shared_ptr<Tab>> Tabs;
};