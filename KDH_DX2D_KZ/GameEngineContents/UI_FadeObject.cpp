#include "PreCompile.h"
#include "UI_FadeObject.h"

UI_FadeObject::UI_FadeObject()
{
}

UI_FadeObject::~UI_FadeObject()
{
}


void UI_FadeObject::Start()
{
	// ���ҽ� �ε�
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_FADE.png"));
			GameEngineSprite::CreateSingle("UI_FADE.png");
		}
	}

	// ������ ����
	FadeObjectRenderer = CreateComponent<GameEngineUIRenderer>(ContentsRenderType::Skyline);
	FadeObjectRenderer->SetSprite("UI_FADE.png");

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	FadeObjectRenderer->Transform.SetLocalScale(WindowScale);

//
//	std::shared_ptr<GameEngineMaterial> material = FadeObjectRenderer->GetMaterial();
//
//	material->data
//
////	GameEngineDebug::DrawBox2D(FadeObjectRenderer->Transform);
//
//	FadeColor = GameEngineColor::BLACK;


}

// ���¸� Ȯ���ϰ� ���� ��带 ���ڷ� �Է¹��� ���� �����մϴ�.
void UI_FadeObject::SwitchFadeMode(EFADE_STATE _ChangeState)
{
	FadeState = _ChangeState;

	if (FadeState == EFADE_STATE::In)
	{
		CurrentAlpha = 255.0f;
	}

	else
	{
		CurrentAlpha = 0.0f;
	}
}

void UI_FadeObject::Fade(float _Delta)
{

	//if (FadeState == EFADE_STATE::In)
	//{
	//	CurrentAlpha -= _Delta * 100;
	//	if (0.0f >= CurrentAlpha)
	//	{
	//		Death();
	//		return;
	//	}
	//}

	FadeObjectRenderer->GetCurSprite().Texture->Test(_Delta);

}


void UI_FadeObject::Update(float _Delta)
{
	Fade(_Delta);

	if (GetLiveTime() > 1.0f)
	{
		Death();
	}
}

//
//void UI_FadeObject::StateUpdate(float _Delta)
//{
//}