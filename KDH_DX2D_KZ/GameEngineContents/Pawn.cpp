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
		MsgBoxAssert("ERROR : 존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다. 입력한 텍스처 이름을 다시 확인하세요.");
	}
}

GameEngineColor Pawn::GetMapColor(float4 _Pos, GameEngineColor _DefaultColor)
{

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("ERROR : 땅 체크용 텍스처가 존재하지 않습니다. 먼저 레벨에서 텍스처를 지정해주세요.");
	}

	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	return MapTexture->GetColor(_Pos, _DefaultColor);
}

void Pawn::SetInitStat()
{
}

void Pawn::OnDamaged(int _iAttackPower)
{
}
