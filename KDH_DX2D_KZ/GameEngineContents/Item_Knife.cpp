#include "PreCompile.h"
#include "Item_Knife.h"

Item_Knife::Item_Knife()
{
}

Item_Knife::~Item_Knife()
{
}

void Item_Knife::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Object\\spr_knife\\");

		GameEngineTexture::Load(FilePath.PlusFilePath("spr_knife_0.png"));
		GameEngineSprite::CreateSingle("spr_knife_0.png");
	}

	KnifeMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	KnifeMainRenderer->SetSprite("spr_knife_0.png");
	KnifeMainRenderer->AutoSpriteSizeOn();

}

void Item_Knife::Update(float _Delta)
{

	static const float4 gravity = { 0.0f, -9.8f };
	static const float coef_res = 0.5f;

	if (GetLiveTime() < 0.3f)
	{
		Transform.AddLocalPosition(MovePos * Speed * _Delta);
	}

	else if (GetLiveTime() > 0.3f && GetLiveTime() < 1.0f)
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 5.0f });

		Velocity += gravity * _Delta;

		Transform.AddLocalPosition(Velocity);

		// 아래
		if (-535.0f > Transform.GetLocalPosition().Y)
		{
			MovePos = float4::ZERO;
			Velocity = 0.0f;
		}

		//else
		//{
		//	// 위
		//	if (-204.0f < Transform.GetLocalPosition().Y)
		//	{
		//		MovePos = { (float4::LEFT + float4::DOWN) * coef_res };
		//	}

		//	// 오른쪽
		//	else if (1128.0f < Transform.GetLocalPosition().X)
		//	{
		//		MovePos = { (float4::LEFT + float4::DOWN) * coef_res };
		//	}

		//	// 왼쪽
		//	else if (160.0f > Transform.GetLocalPosition().X)
		//	{
		//		MovePos = { (float4::RIGHT + float4::DOWN) * coef_res };
		//	}
		//}

	}




}
