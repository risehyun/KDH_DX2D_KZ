#include "PreCompile.h"
#include "Laser.h"
#include "Player.h"
#include "Enemy.h"

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

	{
		GameEngineTexture::Load(FilePath.PlusFilePath("spr_ceiling_laser_back_short.png"));
		GameEngineSprite::CreateSingle("spr_ceiling_laser_back_short.png");
	}

	{
		GameEngineTexture::Load(FilePath.PlusFilePath("spr_ceiling_laser_back_long.png"));
		GameEngineSprite::CreateSingle("spr_ceiling_laser_back_long.png");
	}

	LaserCeilingRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::PlayFront));
	LaserCeilingRenderer->SetSprite("spr_ceiling_laser_on.png");
	LaserCeilingRenderer->Transform.SetLocalPosition({ 0.0f, 85.0f });
	LaserCeilingRenderer->AutoSpriteSizeOn();

	LaserMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	LaserMainRenderer->AutoSpriteSizeOn();

	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->SetCollisionType(ColType::AABBBOX2D);
	InteractCollision->Transform.SetLocalScale({ 10.0f, 190.0f });

	LaserAuraRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::PlayFront));
	LaserAuraRenderer->SetSprite("spr_ceiling_laser_back_short.png");
	LaserAuraRenderer->AutoSpriteSizeOn();
	LaserAuraRenderer->Transform.SetLocalPosition({ 0.0f, -10.0f });

}

void Laser::Update(float _Delta)
{
	LaserDetectPlayerEvent();
	LaserDetectEnemyEvent();
}

void Laser::InitLaserData(bool _UseLongType)
{
	IsLongType = _UseLongType;

	// long일때 y값 -60, short 일때 -10
	// LONG LASER
	if (true == IsLongType)
	{
		LaserAuraRenderer->SetSprite("spr_ceiling_laser_back_long.png");
		LaserAuraRenderer->Transform.SetLocalPosition({ 0.0f, -65.0f });

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

void Laser::LaserDetectPlayerEvent()
{
	EventParameter LaserDetectEnemyEvent;

	LaserDetectEnemyEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

		if (true == LaserPtr->LaserAuraRenderer->GetUpdateValue())
		{
			LaserPtr->LaserAuraRenderer->Off();
		}

		if (true == LaserPtr->IsLongType)
		{
			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserDetect_Long");
		}
		else
		{
			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserDetect_Short");
		}

		if (false == Player::MainPlayer->GetPlayerImmortalMode())
		{
			Player::MainPlayer->FSM_PlayerState.ChangeState(FSM_PlayerState::Death);
		}

	};

	LaserDetectEnemyEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

		if (false == LaserPtr->LaserAuraRenderer->GetUpdateValue())
		{
			LaserPtr->LaserAuraRenderer->On();
		}

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

void Laser::LaserDetectEnemyEvent()
{
	EventParameter LaserDetectEnemyEvent;

	LaserDetectEnemyEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

		GameEngineActor* EnemyActor = Col->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(EnemyActor);


		if (true == LaserPtr->LaserAuraRenderer->GetUpdateValue())
		{
			LaserPtr->LaserAuraRenderer->Off();
		}

		if (true == LaserPtr->IsLongType)
		{
			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserDetect_Long");
		}
		else
		{
			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserDetect_Short");
		}

		EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Death);

	};

	LaserDetectEnemyEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Laser* LaserPtr = dynamic_cast<Laser*>(thisActor);

		if (false == LaserPtr->LaserAuraRenderer->GetUpdateValue())
		{
			LaserPtr->LaserAuraRenderer->On();
		}

		if (true == LaserPtr->IsLongType)
		{
			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserFlow_Long");
		}
		else
		{
			LaserPtr->LaserMainRenderer->ChangeAnimation("LaserFlow_Short");
		}

	};

	InteractCollision->CollisionEvent(ContentsCollisionType::EnemyBody, LaserDetectEnemyEvent);
}
