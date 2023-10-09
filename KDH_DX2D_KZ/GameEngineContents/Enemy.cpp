#include "PreCompile.h"
#include "Enemy.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "Bullet.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::InitEnemyData()
{
	{
		EnemyMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		EnemyMainRenderer->AutoSpriteSizeOn();


		if (Type == EnemyType::NormalGangster)
		{
			SetCharacterType(CharacterType::NormalEnemy);

			EnemyMainRenderer->CreateAnimation("Idle", "spr_gangsteridle");
			EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);
			EnemyMainRenderer->CreateAnimation("Turn", "spr_gangsterturn", 0.2f, 0, 5, false);

			EnemyMainRenderer->ChangeAnimation("Idle");
		}


		if (Type == EnemyType::ColoredGangster)
		{
			SetCharacterType(CharacterType::ObjectEnemy);
			EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground2", 0.4f, 0, 5, false);
			ChangeState(EnemyState::Death);
		}

	}

	{
		EnemyEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		EnemyEffectRenderer->Transform.SetLocalPosition({ 70.0f, -4.f, 0.f, 1.f });

		EnemyEffectRenderer->CreateAnimation("GunSpark", "spr_gunspark");
		EnemyEffectRenderer->AutoSpriteSizeOn();
		EnemyEffectRenderer->Off();

	}

	EnemyMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyBody);
	EnemyMainCollision->Transform.SetLocalScale({ 30, 30, 1 });

}

void Enemy::SetEnemyData(EnemyType _EnemyType)
{
	Type = _EnemyType;

	InitEnemyData();
}

void Enemy::ChangeEmotion(EEnemyState_Emotion _NextEmotion)
{
	if (_NextEmotion != EmotionState)
	{
		switch (_NextEmotion)
		{
		case EEnemyState_Emotion::Question:
			EnemyEmotionRenderer->SetSprite("spr_enemy_question.png");
			EnemyEmotionRenderer->On();
			break;

		case EEnemyState_Emotion::NormalExclamation:
			EnemyEmotionRenderer->SetSprite("spr_enemy_follow_1.png");
			EnemyEmotionRenderer->On();
			break;

		case EEnemyState_Emotion::HardExclamation:
			EnemyEmotionRenderer->SetSprite("spr_enemy_follow_0.png");
			EnemyEmotionRenderer->On();
			break;

		case EEnemyState_Emotion::Default:
			EnemyEmotionRenderer->Off();
			break;

		default:
			break;
		}
	}

	EmotionState = _NextEmotion;

}

void Enemy::UpdateEmotion(float _Delta)
{


}

void Enemy::ChangeState(EnemyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case EnemyState::Idle:
			IdleStart();
			break;

		case EnemyState::Run:
			RunStart();
			break;

		case EnemyState::Attack:
			AttackStart();
			break;

		case EnemyState::Death:
			DeathStart();
			break;

		case EnemyState::Turn:
			TurnStart();
			break;

		default:
			break;
		}
	}

	State = _State;

}

void Enemy::StateUpdate(float _Delta)
{
	switch (State)
	{
	case EnemyState::Idle:
		return IdleUpdate(_Delta);

	case EnemyState::Run:
		return RunUpdate(_Delta);

	case EnemyState::Attack:
		return AttackUpdate(_Delta);

	case EnemyState::Death:
		return DeathUpdate(_Delta);

	case EnemyState::Turn:
		return TurnUpdate(_Delta);

	default:
		break;
	}
}

void Enemy::DirCheck()
{
}

void Enemy::ChangeAnimationState(std::string_view _StateName)
{
}

void Enemy::TurnStart()
{
	EnemyMainRenderer->ChangeAnimation("Turn");
}

void Enemy::TurnUpdate(float _Delta)
{
	if (EnemyMainRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Idle);
	}
}

void Enemy::IdleStart()
{
	EnemyMainRenderer->ChangeAnimation("Idle");
}

void Enemy::IdleUpdate(float _Delta)
{
}

void Enemy::RunStart()
{
}

void Enemy::RunUpdate(float _Delta)
{
}

void Enemy::AttackStart()
{
	EnemyEffectRenderer->On();
	EnemyEffectRenderer->ChangeAnimation("GunSpark");

	// Bullet 세팅
	{
		std::shared_ptr<Bullet> EnemyNewBullet = GetLevel()->CreateActor<Bullet>(static_cast<int>(ContentsRenderType::Play));
		EnemyNewBullet->InitBulletData(ContentsCollisionType::EnemyAttack, float4::RIGHT, 0.5f, false);
		EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y });
	}
}

void Enemy::AttackUpdate(float _Delta)
{
	if (true == EnemyEffectRenderer->IsCurAnimationEnd())
	{
		EnemyEffectRenderer->Off();
	}
}

void Enemy::DeathStart()
{
	EnemyMainRenderer->ChangeAnimation("Death");



}

void Enemy::DeathUpdate(float _Delta)
{

	if (Type != EnemyType::ColoredGangster)
	{

		float4 CheckPos = { Transform.GetWorldPosition() + DownCheck };
		float4 MovePos = { 0.0f, -Speed * _Delta * 2.0f };


		GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);
		if (Color == GameEngineColor::WHITE)
		{
			Transform.AddLocalPosition(MovePos);
		}
	}

	if (Type == EnemyType::ColoredGangster && GetLiveTime() < 1.0f)
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed * 1.5f);
	}

	if (EnemyMainRenderer->IsCurAnimationEnd())
	{
		EnemyMainCollision->Off();
		EnemyEmotionRenderer->Off();
		ChangeState(EnemyState::Default);
	}

	//if (Type == EnemyType::ColoredGangster)
	//{
	//	EnemyMainCollision->Off();
	//}

}

void Enemy::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_enemy_exclaim_0.png"));
			GameEngineSprite::CreateSingle("spr_enemy_exclaim_0.png");

			GameEngineTexture::Load(FilePath.PlusFilePath("spr_enemy_exclaim_1.png"));
			GameEngineSprite::CreateSingle("spr_enemy_exclaim_1.png");

			GameEngineTexture::Load(FilePath.PlusFilePath("spr_enemy_follow_0.png"));
			GameEngineSprite::CreateSingle("spr_enemy_follow_0.png");

			GameEngineTexture::Load(FilePath.PlusFilePath("spr_enemy_follow_1.png"));
			GameEngineSprite::CreateSingle("spr_enemy_follow_1.png");

			GameEngineTexture::Load(FilePath.PlusFilePath("spr_enemy_question.png"));
			GameEngineSprite::CreateSingle("spr_enemy_question.png");
		}
	}

	EnemyEmotionRenderer  = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	EnemyEmotionRenderer->SetSprite("spr_enemy_question.png");
	EnemyEmotionRenderer->AutoSpriteSizeOn();

	EnemyEmotionRenderer->Transform.SetLocalPosition({ 0.0f, 42.0f, 0.0f, 1.0f });
	EnemyEmotionRenderer->Off();

}

void Enemy::Update(float _Delta)
{

	Gravity(_Delta);

	StateUpdate(_Delta);






	// 충돌 이벤트 설정 -> 함수로 빼기
	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(thisActor);

		GameEngineActor* PlayerAttackActor = Col->GetActor();
		Col->Death();

		EnemyPtr->ChangeState(EnemyState::Death);
	};

	EnemyMainCollision->CollisionEvent(ContentsCollisionType::PlayerAttack, Event);
}
