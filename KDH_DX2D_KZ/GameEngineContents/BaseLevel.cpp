#include "PreCompile.h"
#include "BaseLevel.h"
#include "Player.h"
#include "GameStateManager.h"

BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::Start()
{
	// 레벨이 Input 가능한 상태로 만듦
	GameEngineInput::AddInputObject(this);
//
//#pragma region Level FSM 등록
//
//	// ★ 레벨마다 들어가는 FSM이 있고 아닌게 있기 때문에... 이것도 고민해서 조정해야 할 것 같다.
//	FSM_Level_PlayGame();
//	FSM_Level_SlowGame();
//
//	LevelState.ChangeState(LevelState::PlayGame);
//
//#pragma endregion
//
//#pragma region 레벨 효과음 로딩
//	// ★ 상위 레벨 클래스로 옮기기
//	
//		GameEnginePath FilePath;
//		FilePath.SetCurrentPath();
//		FilePath.MoveParentToExistsChild("ContentsResources");
//		FilePath.MoveChild("ContentsResources\\Sound\\FX\\PlayerFX\\");
//
//		if (nullptr == GameEngineSound::FindSound("sound_slomo_disengage.wav"))
//		{
//			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_disengage.wav"));
//		}
//
//		if (nullptr == GameEngineSound::FindSound("sound_slomo_engage.ogg"))
//		{
//			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_slomo_engage.ogg"));
//		}
//	
//#pragma endregion

}

void BaseLevel::Update(float _Delta)
{
	// Level FSM 작동
//	LevelState.Update(_Delta);

}

void BaseLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
//	InitCameraSetting();

	{
		std::shared_ptr<GameStateManager> Object = CreateActor<GameStateManager>();
	}
}

void BaseLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void BaseLevel::InitCameraSetting()
{
//	1280 * 720

//	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	CameraInitPos = { 640.0f, -360.0f, -500.0f };

	GetMainCamera()->Transform.SetLocalPosition(CameraInitPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	GetUICamera()->Transform.SetLocalPosition({ 640.0f, 300.0f, -500.0f });
}
