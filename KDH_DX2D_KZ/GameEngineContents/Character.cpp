#include "PreCompile.h"
#include "Character.h"
#include "GameStateManager.h"
#include "Player.h"

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
		GravityVector += { float4::DOWN * GravityPower * _Delta };
	}

	else
	{
		GravityReset();
	}

	Transform.AddWorldPosition(GravityVector * _Delta);
}

// 모든 캐릭터는 해당 Color 위치를 기준으로 땅을 판별합니다.
bool Character::GetGroundPixelCollision()
{
	GameEngineColor Color;

	// 스위치 문으로 바꿔주기
	if (CharType == CharacterType::NormalEnemy)
	{
		// 적의 경우 Idle에서 -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 40.0f }, GameEngineColor::RED);
	}

	else if (CharType == CharacterType::Player || CharType == CharacterType::Boss)
	{
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 40.0f }, GameEngineColor::RED);
	}

	else if (CharType == CharacterType::BossHead)
	{
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 10.0f }, GameEngineColor::RED);
	}

	else
	{
		// 적의 경우 Idle에서 -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 32.0f }, GameEngineColor::RED);
	}

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
