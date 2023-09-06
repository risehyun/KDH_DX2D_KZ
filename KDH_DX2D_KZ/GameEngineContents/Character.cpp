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

	// 가장기본적인 물리는 모든힘이 다 +진게 나의 이동 방햐이 된다.
	GravityVector += float4::DOWN * GravityPower * _Delta;

	Transform.AddLocalPosition(GravityVector * _Delta);
}

float4 Character::ActorCameraPos()
{
	return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
}
