#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Map.h"
#include "Enemy.h"
#include "UI_PlayUI.h"

class MainLevel1_1 : public GameEngineLevel
{
public:
	// constrcuter destructer
	MainLevel1_1();
	~MainLevel1_1();

	// delete Function
	MainLevel1_1(const MainLevel1_1& _Other) = delete;
	MainLevel1_1(MainLevel1_1&& _Other) noexcept = delete;
	MainLevel1_1& operator=(const MainLevel1_1& _Other) = delete;
	MainLevel1_1& operator=(MainLevel1_1&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void ShakeCamera(float _Delta);

private:
	std::shared_ptr<Map> MapObject;

	GameEngineSoundPlayer BGMPlayer;

	float4 CameraInitPos;

	std::vector<std::shared_ptr<Enemy>> AllEnemy;

	enum class ELevelState
	{
		Intro,		 // 페이드 오브젝트, 카메라 쉐이크, 에너미 떨어짐, 두리번거리기
		PlayerSpawn, // 플레이어 스폰, 이동
		TimeControl, // 시간 조작, 패링, 플레이어 자동 이동(조작불가), 플레이어 바닥 착지
		StartGame,   // 플레이어 조작 가능, 커서 생성
		Default,
	};

	ELevelState LevelState = ELevelState::Default;

	void ChangeLevelState(ELevelState _NextLevelState);
	void UpdateLevelState(float _Delta);

	void FSM_Intro_Start();
	void FSM_PlayerSpawn_Start();
	void FSM_TimeControl_Start();
	void FSM_StartGame_Start();

	void FSM_Intro_Update(float _Delta);
	void FSM_PlayerSpawn_Update(float _Delta);
	void FSM_TimeControl_Update(float _Delta);
	void FSM_StartGame_Update(float _Delta);

	std::shared_ptr<UI_PlayUI> PlayUIObject = nullptr;
};

