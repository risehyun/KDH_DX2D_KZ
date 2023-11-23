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
	// �߷��� ������� �ʴ� ��� �����Ͽ� �Ʒ��� �Լ��� ������� �ʵ��� �մϴ�.
	if (false == IsGravity)
	{
		return;
	}

	// ����� �ִ� ���
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

// ��� ĳ���ʹ� �ش� Color ��ġ�� �������� ���� �Ǻ��մϴ�.
bool Character::GetGroundPixelCollision()
{
	GameEngineColor Color;

	// ����ġ ������ �ٲ��ֱ�
	if (CharType == CharacterType::NormalEnemy)
	{
		// ���� ��� Idle���� -50
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
		// ���� ��� Idle���� -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 32.0f }, GameEngineColor::RED);
	}

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
