#include "PreCompile.h"
#include "Item_Knife.h"
#include "Player.h"
#include "UI_PlayUI.h"

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

	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });

	KnifeMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	KnifeMainRenderer->SetSprite("spr_knife_0.png");
	KnifeMainRenderer->AutoSpriteSizeOn();

	PickUpArrowMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	PickUpArrowMainRenderer->AutoSpriteSizeOn();
	PickUpArrowMainRenderer->CreateAnimation("PickUpArrow", "spr_pickuparrow_anim");
	PickUpArrowMainRenderer->ChangeAnimation("PickUpArrow");
	PickUpArrowMainRenderer->Transform.SetLocalPosition({ 0.0f, 70.0f });
	PickUpArrowMainRenderer->Off();

	GameEngineInput::AddInputObject(this);
}

void Item_Knife::Update(float _Delta)
{
	MovingArrow(_Delta);
	GetItemEvent();

	static const float4 gravity = { 0.0f, -9.8f };
	static const float coef_res = 0.5f;

	if (GetLiveTime() < 0.3f)
	{
		Transform.AddLocalPosition(MovePos * Speed * _Delta);
	}

	else if (GetLiveTime() > 0.3f && GetLiveTime() < 1.0f)
	{
		KnifeMainRenderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 5.0f });

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
	else
	{
		if (false == PickUpArrowMainRenderer->GetUpdateValue())
		{
			PickUpArrowMainRenderer->On();
		}
	}
}

void Item_Knife::MovingArrow(float _Delta)
{
	ArrowMoveTimer += _Delta;

	if (ArrowMoveTimer < 0.5f)
	{
		PickUpArrowMainRenderer->Transform.AddLocalPosition({ 0.0f, -1.0f });
	}
	else if (ArrowMoveTimer > 0.5f && ArrowMoveTimer < 1.0f)
	{
		PickUpArrowMainRenderer->Transform.AddLocalPosition({ 0.0f, 1.0f });
	}
	else if (ArrowMoveTimer > 1.0f)
	{
		PickUpArrowMainRenderer->Transform.SetLocalPosition({ 0.0f, 70.0f });
		ArrowMoveTimer = 0.0f;
	}
}

void Item_Knife::GetItemEvent()
{
	EventParameter Event;

	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		if (GameEngineInput::IsPress(VK_SPACE, this) && this != nullptr)
		{
			// ITEM 
			UI_PlayUI::PlayUI->SetItemUI("spr_knife_0.png");
			Death();
		}
	};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		if (GameEngineInput::IsPress(VK_SPACE, this) && this != nullptr)
		{
			UI_PlayUI::PlayUI->SetItemUI("spr_knife_0.png");
			Death();
		}
	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, Event);

}
