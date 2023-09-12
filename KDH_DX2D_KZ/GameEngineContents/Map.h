#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

class Map : public GameEngineActor
{
public:
	Map();
	~Map();

	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void InitMap(std::string_view _MapName);
	void InitDebuggedMap(std::string_view _MapName, std::string_view _DebugMapName);
	void SwitchingRender();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	bool SwitchRenderValue = true;

	std::string_view MapName;
	std::string_view DebugMapName;
	
	std::shared_ptr<GameEngineSpriteRenderer> MapRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DebugMapRenderer;

};

