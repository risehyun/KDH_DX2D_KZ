#include "PreCompile.h"
#include "Pawn.h"

Pawn::Pawn()
{
}

Pawn::~Pawn()
{
}

void Pawn::SetMapTexture(std::string_view _MapTextureName)
{
	MapTexture = GameEngineTexture::Find(_MapTextureName);

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("ERROR : �������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�. �Է��� �ؽ�ó �̸��� �ٽ� Ȯ���ϼ���.");
	}
}

//GameEngineColor Pawn::GetMapColor(unsigned int _DefaultColor, float4 _Pos)
//{
//	if (nullptr == MapTexture)
//	{
//		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�.");
//	}
//
//	return MapTexture->GetColor(Transform.GetWorldPosition() + _Pos, GameEngineColor::RED);
//
//}

GameEngineColor Pawn::GetMapColor(float4 _Pos, GameEngineColor _DefaultColor)
{

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�. ���� �������� �ؽ�ó�� �������ּ���.");
	}

		// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
		// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
		_Pos.Y *= -1.0f;

//		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Map_MainLevel1.png");


		return MapTexture->GetColor(_Pos, _DefaultColor);
}

void Pawn::SetInitStat()
{
}

void Pawn::OnDamaged(int _iAttackPower)
{
}
