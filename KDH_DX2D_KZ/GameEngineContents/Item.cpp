#include "PreCompile.h"
#include "Item.h"
#include "UI_PlayUI.h"
#include "Player.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Start()
{
	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });

	PickUpArrowMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	PickUpArrowMainRenderer->AutoSpriteSizeOn();
	PickUpArrowMainRenderer->CreateAnimation("PickUpArrow", "spr_pickuparrow_anim");
	PickUpArrowMainRenderer->ChangeAnimation("PickUpArrow");
	PickUpArrowMainRenderer->Transform.SetLocalPosition({ 0.0f, 70.0f });
	PickUpArrowMainRenderer->Off();

	GameEngineInput::AddInputObject(this);
}

void Item::Update(float _Delta)
{
	MovingPickUpArrow(_Delta);
	CollisonEvent_DetectPlayer();

	ItemDrop(_Delta);
}

void Item::SetItemData(EItemType _ItemType)
{
	ItemType = _ItemType;

	switch (ItemType)
	{
	case EItemType::Knife:
		ItemSpriteName = "spr_knife_0.png";
		break;

	case EItemType::Default:
		break;

	default:
		break;
	}

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Object\\Item\\");

		GameEngineTexture::Load(FilePath.PlusFilePath(ItemSpriteName));
		GameEngineSprite::CreateSingle(ItemSpriteName);
	}

	ItemMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	ItemMainRenderer->SetSprite(ItemSpriteName);
	ItemMainRenderer->AutoSpriteSizeOn();
}

void Item::SetItemSlot()
{
	UI_PlayUI::PlayUI->SetItemSlot(ItemSpriteName);
}

void Item::ItemDrop(float _Delta)
{
	static const float4 gravity = { 0.0f, -9.8f };
	static const float coef_res = 0.5f;

	if (GetLiveTime() < 0.3f)
	{
		Transform.AddLocalPosition(MovePos * Speed * _Delta);
	}

	else if (GetLiveTime() > 0.3f && GetLiveTime() < 3.0f)
	{

		if (GetLiveTime() < 1.0f)
		{
			ItemMainRenderer->Transform.AddLocalRotation({ 0.0f, 0.0f, 1.0f * _Delta * Speed });
		}

		// ¾Æ·¡
		if (-535.0f > Transform.GetLocalPosition().Y)
		{
			MovePos = float4::ZERO;
			Velocity = 0.0f;

			if (false == PickUpArrowMainRenderer->GetUpdateValue())
			{
				PickUpArrowMainRenderer->On();
			}
		}
		else
		{
			Velocity += gravity * _Delta;

			Transform.AddLocalPosition(Velocity);
		}
	}
}

void Item::CollisonEvent_DetectPlayer()
{
	EventParameter Event;

	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		if (true == Player::MainPlayer->Get_PlayerDashable())
		{
			Player::MainPlayer->Off_PlayerDashable();
		}

		if (GameEngineInput::IsPress(VK_RBUTTON, this) && this != nullptr)
		{
			SetItemSlot();
			Death();
		}
	};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		if (true == Player::MainPlayer->Get_PlayerDashable())
		{
			Player::MainPlayer->Off_PlayerDashable();
		}

		if (GameEngineInput::IsPress(VK_RBUTTON, this) && this != nullptr)
		{
			SetItemSlot();
			Death();
		}
	};

	Event.Exit = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		if (false == Player::MainPlayer->Get_PlayerDashable())
		{
			Player::MainPlayer->On_PlayerDashable();
		}
	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, Event);

}

void Item::MovingPickUpArrow(float _Delta)
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
