#include "PreCompile.h"
#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Gravity(float _Delta)
{
	// �߷��� ������� �ʴ� ��� �����Ͽ� �Ʒ��� �Լ��� ������� �ʵ��� �մϴ�.
	if (false == IsGravity)
	{
		return;
	}

	// ����� �ִ� ���
	if (true == GetGroundPixelCollision())
	{
		GravityForce.Y -= _Delta * 100.0f;
	}

	// ����� �ƴ� ��� (���� �ִ� ���)
	else
	{


		//GameEngineColor CheckColor = GetMapColor(float4::UP, GameEngineColor::WHITE);

		//while (CheckColor != GameEngineColor::WHITE)
		//{
		//	CheckColor = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 1.0f }, GameEngineColor::WHITE);
		//	Transform.AddLocalPosition(float4::UP);
		//}




		//if (CheckColor == GameEngineColor::RED)
		//{
		//	Transform.AddLocalPosition(float4::UP * 30.0f);
		//}




		// �߷°��� ������� �ʽ��ϴ�.
		GravityForce = 0.0f;

		GravityReset();

	}

	Transform.AddLocalPosition(GravityForce * _Delta);
}

bool Character::GetGroundPixelCollision()
{

	GameEngineColor Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 30.0f }, GameEngineColor::RED);
	if (GameEngineColor::WHITE == Color)
	{
		return true;
	}

	// ����� �ƴ� ��� (���� �ִ� ���)
	else
	{
		return false;
	}
	
}

float4 Character::ActorCameraPos()
{
	return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
}
