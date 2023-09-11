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
		GravityVector += float4::DOWN * GravityPower * _Delta;
	}

	else
	{
		// �߷°��� ������� �ʽ��ϴ�.
		GravityForce = 0.0f;
		GravityReset();

	}

	Transform.AddLocalPosition(GravityVector * _Delta);
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
