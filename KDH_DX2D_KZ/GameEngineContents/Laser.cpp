#include "PreCompile.h"
#include "Laser.h"
#include "Player.h"

Laser::Laser()
{
}

Laser::~Laser()
{
}

// ★ 길이 설정, 움직임 유무 설정 필요
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
	InteractCollision->Transform.SetLocalScale({ 100, 100, 1 });

	MoveDir = { 1.0f, 0.0f };
}

void Laser::Update(float _Delta)
{
	LaserDetectEnemyEvent();

	if (true == IsUseMoving)
	{
		// MAX : 1200.0f

		Transform.AddLocalPosition({ MoveDir * _Delta * 200.0f });

		//OutputDebugStringA(std::to_string(Transform.GetLocalPosition().X + 'N').c_str() );

		if (Transform.GetLocalPosition().X >= 1200.0f)
		{
			MoveDir = { -1.0f, 0.0f };
		}

		if (Transform.GetLocalPosition().X < 780.0f)
		{
			MoveDir = { 1.0f, 0.0f };
		}

		//if (Transform.GetLocalPosition().X > 500.0f)
		//{
		//	MoveDir = { -1.0f, 0.0f, 0.0f };
		//}
		
	}
}

void Laser::InitLaserData(bool _UseLongType, bool _UseMoving)
{
	IsLongType = _UseLongType;
	IsUseMoving = _UseMoving;

	// long일때 y값 -60, short 일때 -10
// LONG LASER
	if (true == IsLongType)
	{
		LaserMainRenderer->Transform.SetLocalPosition({ 0.0f, -60.0f });
		LaserMainRenderer->CreateAnimation("LaserFlow_Long", "LaserLong_Normal");
		LaserMainRenderer->CreateAnimation("LaserDetect_Long", "LaserLong_Detected");
		LaserMainRenderer->ChangeAnimation("LaserFlow_Long");
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
