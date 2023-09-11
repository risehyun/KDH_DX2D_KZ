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
	// 중력을 사용하지 않는 경우 리턴하여 아래의 함수가 실행되지 않도록 합니다.
	if (false == IsGravity)
	{
		return;
	}

	// 허공에 있는 경우
	if (true == GetGroundPixelCollision())
	{
		GravityVector += float4::DOWN * GravityPower * _Delta;
	}

	else
	{
		// 중력값을 사용하지 않습니다.
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

	// 허공이 아닌 경우 (땅에 있는 경우)
	else
	{
		return false;
	}
	
}

float4 Character::ActorCameraPos()
{
	return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
}
