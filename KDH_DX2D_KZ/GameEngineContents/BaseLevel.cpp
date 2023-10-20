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
	// ������ Input ������ ���·� ����
	GameEngineInput::AddInputObject(this);
//
//#pragma region Level FSM ���
//
//	// �� �������� ���� FSM�� �ְ� �ƴѰ� �ֱ� ������... �̰͵� ����ؼ� �����ؾ� �� �� ����.
//	FSM_Level_PlayGame();
//	FSM_Level_SlowGame();
//
//	LevelState.ChangeState(LevelState::PlayGame);
//
//#pragma endregion
//
//#pragma region ���� ȿ���� �ε�
//	// �� ���� ���� Ŭ������ �ű��
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
	// Level FSM �۵�
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
