#include "PreCompile.h"
#include "Laser.h"
#include "Player.h"

Laser::Laser()
{
}

Laser::~Laser()
{
}

// �� ���� ����, ������ ���� ���� �ʿ�
void Laser::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\Texture\\Object\\Laser\\");
	{
		GameEngineTexture::Load(FilePath.PlusFilePath("spr_ceiling_laser_on.png"));
		GameEngineSprite::CreateSingle("spr_ceiling_laser_on.png");
	}

	LaserCeilingRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::PlayFront));
	LaserCeilingRenderer->SetSprite("spr_ceiling_laser_on.png");
	LaserCeilingRenderer->Transform.SetLocalPosition({ 0.0f, 85.0f });
	LaserCeilingRenderer->AutoSpriteSizeOn();
	LaserCeilingRenderer->On();

	LaserMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	LaserMainRenderer->AutoSpriteSizeOn();

	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->SetCollisionType(ColType::AABBBOX2D);
	InteractCollision->Transform.SetLocalScale({ 10.0f, 190.0f });

	MoveDir = { 1.0f, 0.0f };
}

void Laser::Update(float _Delta)
{
	LaserDetectEnemyEvent();
}

void Laser::InitLaserData(bool _UseLongType)
{
	IsLongType = _UseLongType;

	// long�϶� y�� -60, short �϶� -10
	// LONG LASER
	if (true == IsLongType)
	{
		LaserMainRenderer->Transform.SetLocalPosition({ 0.0f, -60.0f });
		LaserMainRenderer->CreateAnimation("LaserFlow_Long", "LaserLong_Normal");
		LaserMainRenderer->CreateAnimation("LaserDetect_Long", "LaserLong_Detected");
		LaserMainRenderer->ChangeAnimation("LaserFlow_Long");

		InteractCollision->Transform.SetLocalScale({ 10.0f, 280.0f, 1.0f });
		InteractCollision->Transform.SetLocalPosition({ 0.0f, -64.0f });
	}

	// SHORT LASER
	else if (false == IsLongType)
	{
		LaserMainRenderer->Transform.SetLocalPosition({ 0.0f, -10.0f });
		LaserMainRenderer->CreateAnimation("LaserFlow_Short", "LaserShort_Normal");
		LaserMainRenderer->CreateAnimation("LaserDetect_Short", "LaserShort_Detected");
		LaserMainRenderer->ChangeAnimation("LaserFlow_Short");
	}

}

void Laser::LaserDetectEnemyEvent()
{
	EventParameter LaserDetectEnemyEvent;

	LaserDetectEnemyEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* thisActor = _this->GetActor();
			Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

			if (true == LaserPtr->IsLongType)
			{
				LaserPtr->LaserMainRenderer->ChangeAnimation("LaserDetect_Long");
			}
			else
			{
				LaserPtr->LaserMainRenderer->ChangeAnimation("LaserDetect_Short");
			}

		};

	//LaserDetectEnemyEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	//	{

	//	};

	LaserDetectEnemyEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* thisActor = _this->GetActor();
			Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

			if (true == LaserPtr->IsLongType)
			{
				LaserPtr->LaserMainRenderer->ChangeAnimation("LaserFlow_Long");
			}
			else
			{
				LaserPtr->LaserMainRenderer->ChangeAnimation("LaserFlow_Short");
			}

		};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, LaserDetectEnemyEvent);
}
