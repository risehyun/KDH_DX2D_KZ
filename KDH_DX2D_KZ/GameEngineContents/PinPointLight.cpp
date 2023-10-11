#include "PreCompile.h"
#include "PinPointLight.h"

PinPointLight::PinPointLight()
{
}

PinPointLight::~PinPointLight()
{
}

void PinPointLight::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Object\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("PinPointLight.png"));
		GameEngineSprite::CreateSingle("PinPointLight.png");

	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
		Renderer->SetSprite("PinPointLight.png");

		Renderer->AutoSpriteSizeOn();

		// ������ ������ -70(����,������ ���� �ִ밪) ~ 110(���� ���� �ִ밪) 
		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, -70.0f });
	}

}

void PinPointLight::Update(float _Delta)
{
	// ���� ���� �ִ밪�� �����ϱ� ���̸� isMax�� Ȱ��ȭ (ȸ�� ���)
	if (Renderer->Transform.GetLocalRotationEuler().Z > -120.0f)
	{
		isMoving = true;
	}
	else
	{
		isMoving = false;
	}

	// ���� �������� ȸ��)
	if (true == isMoving)
	{
		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 10.0f * _Delta * -Speed });
	}

	//else if (false == isMoving && Renderer->Transform.GetLocalRotationEuler().Z < -10.0f)
	//{
	//	Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 20.0f * _Delta * Speed });

	//}


	//if (false == isMax)
	//{
	//	// �������� �̵�
	//	if (Renderer->Transform.GetLocalRotationEuler().Z > -120.0f)
	//	{
	//		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 10.0f * _Delta * -Speed });
	//	}

	//}

	//else
	//{
	//	if (Renderer->Transform.GetLocalRotationEuler().Z < -60.0f)
	//	{
	//		Renderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 10.0f * _Delta * Speed });
	//	}
	//}

}