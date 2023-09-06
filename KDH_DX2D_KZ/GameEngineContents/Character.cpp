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
	if (false == IsGravity)
	{
		return;
	}

	// ����⺻���� ������ ������� �� +���� ���� �̵� ������ �ȴ�.
	GravityVector += float4::DOWN * GravityPower * _Delta;

	Transform.AddLocalPosition(GravityVector * _Delta);
}

float4 Character::ActorCameraPos()
{
	return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
}
