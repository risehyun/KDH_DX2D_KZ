#include "PreCompile.h"
#include "Enemy.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "Player.h"
#include "Bullet.h"
#include "PlayerCursorSlash.h"
#include "GameStateManager.h"
#include "Fx.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::InitEnemyData()
{

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\FX\\EnemyFX\\");

		if (nullptr == GameEngineSound::FindSound("sound_gun_fire.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_gun_fire.wav"));
		}
	}


	{
		EnemyMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		EnemyMainRenderer->AutoSpriteSizeOn();

		EnemyMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyBody);
		EnemyMainCollision->Transform.SetLocalScale({ 60, 60, 1 });

		EnemyDetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyDetect);



		if (Type == EnemyType::NormalGangster)
		{
			SetCharacterType(CharacterType::NormalEnemy);

			EnemyMainRenderer->CreateAnimation("Idle", "spr_gangsteridle");
			EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground", 0.2f, 0, 5, false);
			EnemyMainRenderer->CreateAnimation("Turn", "spr_gangsterturn", 0.2f, 0, 5, false);

			EnemyMainRenderer->ChangeAnimation("Idle");

			EnemyDetectCollision->SetCollisionType(ColType::AABBBOX2D);
			EnemyDetectCollision->Transform.SetLocalScale({ 450, 5, 1 });
		}

		else if (Type == EnemyType::ColoredGangster)
		{
			SetCharacterType(CharacterType::ObjectEnemy);
			EnemyMainRenderer->CreateAnimation("Death", "spr_gangsterhurtground2", 0.4f, 0, 5, false);
			EnemyDetectCollision->SetCollisionType(ColType::AABBBOX2D);
			EnemyDetectCollision->Transform.SetLocalScale({ 450, 5, 1 });
		}

		else if (Type == EnemyType::ShieldCop)
		{
			SetCharacterType(CharacterType::NormalEnemy);

			EnemyMainRenderer->CreateAnimation("Idle", "spr_shieldcop_idle");
			EnemyMainRenderer->CreateAnimation("Walk", "spr_shieldcop_walk");
			EnemyMainRenderer->CreateAnimation("Run", "spr_shieldcop_run");
			EnemyMainRenderer->CreateAnimation("Knockback", "spr_shieldcop_knockback", 0.33f, 0, 0, true);
			EnemyMainRenderer->CreateAnimation("Attack", "spr_shieldcop_bash");
			EnemyMainRenderer->CreateAnimation("Death", "spr_shieldcop_tragedy_die_1", 0.1f, 0, 14, false);
			EnemyMainRenderer->ChangeAnimation("Idle");

			EnemyDetectCollision->SetCollisionType(ColType::AABBBOX2D);
			EnemyDetectCollision->Transform.SetLocalScale({ 450, 5, 1 });
		}

		else if (Type == EnemyType::Cop)
		{
			SetCharacterType(CharacterType::NormalEnemy);

			EnemyMainRenderer->CreateAnimation("Idle", "cop_idle");
			EnemyMainRenderer->CreateAnimation("Run", "spr_cop_run");
			EnemyMainRenderer->CreateAnimation("Attack", "cop_attack", 2.0f, 0, 0, true);
			EnemyMainRenderer->CreateAnimation("Death", "spr_cop_hurtground", 0.2f, 0, 13, false);
			EnemyMainRenderer->ChangeAnimation("Idle");

			EnemyDetectCollision->SetCollisionType(ColType::AABBBOX2D);
			EnemyDetectCollision->Transform.SetLocalScale({ 450, 5, 1 });
		}

		else if (Type == EnemyType::ShotGunCop)
		{
			SetCharacterType(CharacterType::NormalEnemy);

			EnemyMainRenderer->CreateAnimation("Idle", "spr_shotgun_idle");
			EnemyMainRenderer->CreateAnimation("Walk", "spr_shotgun_walk");
			EnemyMainRenderer->CreateAnimation("Run", "spr_shotgun_run");
			EnemyMainRenderer->CreateAnimation("Attack", "spr_shotgun_attack", 2.0f, 0, 0, true);
			EnemyMainRenderer->CreateAnimation("Death", "spr_shotgun_tragedy_die_4", 0.2f, 0, 11, false);
			EnemyMainRenderer->ChangeAnimation("Idle");

			EnemyDetectCollision->SetCollisionType(ColType::AABBBOX2D);
			EnemyDetectCollision->Transform.SetLocalScale({ 450, 5, 1 });
		}

		else if (Type == EnemyType::FloorTurret)
		{
			SetCharacterType(CharacterType::NormalEnemy);

			EnemyMainRenderer->CreateAnimation("Idle", "spr_floor_turret_Idle");
			EnemyMainRenderer->CreateAnimation("Death", "spr_floor_turret_die", 0.2f, 0, 13, false);
			EnemyMainRenderer->CreateAnimation("Attack", "spr_floor_turret_Idle", 2.0f, 0, 0, true);

			EnemyDetectCollision->SetCollisionType(ColType::AABBBOX2D);
			EnemyDetectCollision->Transform.SetLocalScale({ 450, 5, 1 });
		}

		else if (Type == EnemyType::WallTurret)
		{
			SetCharacterType(CharacterType::NormalEnemy);

			EnemyMainRenderer->CreateAnimation("Idle", "spr_bunker_turret_fromwall", 0.1f, 15, 15, true);
			EnemyMainRenderer->CreateAnimation("Appear", "spr_bunker_turret_fromwall", 0.1f, 0, 15, false);
			EnemyMainRenderer->CreateAnimation("Death", "spr_bunker_turret_wall_dead", 0.2f, 0, 13, false);
			EnemyMainRenderer->CreateAnimation("Attack", "spr_bunker_turret_fromwall", 2.0f, 15, 15, true);

			EnemyMainCollision->Transform.SetLocalScale({ 100.0f, 100.0f });


			EnemyDetectCollision->Transform.SetLocalPosition({ 480.0f, 0.0f });
			EnemyDetectCollision->Transform.SetLocalScale({ 900, 5, 1 });

			// FSM 등록
			FSM_Enemy_Appear();
		}
		

	}

	{
		EnemyEffectRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		EnemyEffectRenderer->Transform.SetLocalPosition({ 70.0f, -4.0f });

		EnemyEffectRenderer->CreateAnimation("GunSpark", "spr_gunspark", 0.1f, 0, 7, false);
		EnemyEffectRenderer->AutoSpriteSizeOn();
		EnemyEffectRenderer->ChangeAnimation("GunSpark");
		EnemyEffectRenderer->Off();


	}

	//std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Left = CreateComponent<GameEngineSpriteRenderer>(30);
	//DebugRenderer_Left->AutoSpriteSizeOn();
	//DebugRenderer_Left->SetSprite("Test.bmp");
	//DebugRenderer_Left->Transform.SetLocalPosition(LeftCheck);

	//std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Right = CreateComponent<GameEngineSpriteRenderer>(30);
	//DebugRenderer_Right->AutoSpriteSizeOn();
	//DebugRenderer_Right->SetSprite("Test.bmp");
	//DebugRenderer_Right->Transform.SetLocalPosition(RightCheck);

	//std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Up = CreateComponent<GameEngineSpriteRenderer>(30);
	//DebugRenderer_Up->AutoSpriteSizeOn();
	//DebugRenderer_Up->SetSprite("Test.bmp");
	//DebugRenderer_Up->Transform.SetLocalPosition(UpCheck);

	//std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Down = CreateComponent<GameEngineSpriteRenderer>(30);
	//DebugRenderer_Down->AutoSpriteSizeOn();
	//DebugRenderer_Down->SetSprite("Test.bmp");
	//DebugRenderer_Down->Transform.SetLocalPosition(DownCheck);

	if (Type != EnemyType::WallTurret)
	{

		if (Dir == EnemyDir::Right)
		{
			EnemyMainRenderer->RightFlip();
			EnemyDetectCollision->Transform.SetLocalPosition({ 170.0f, 0.0f });
		}
		else
		{
			EnemyMainRenderer->LeftFlip();
			EnemyDetectCollision->Transform.SetLocalPosition({ -170.0f, 0.0f });
		}
	}


	// FSM 등록
	// Turret 포함 모든 Enemy가 공통으로 가지고 있음
	FSM_Enemy_Idle();
	FSM_Enemy_Death();
	FSM_Enemy_Attack();

	// Turret을 제외한 인간형 Enemy가 가지고 있음
	if ((Type != EnemyType::FloorTurret) && (Type != EnemyType::WallTurret))
	{
		FSM_Enemy_Chase();
	}

	// 역 재생용 렌더러 세팅
	AddRecordingRenderer(EnemyMainRenderer);

	FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);

}

void Enemy::SetEnemyData(EnemyType _EnemyType, EnemyDir _InitDir)
{
	Type = _EnemyType;

	InitDir = _InitDir;
	Dir = InitDir;

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

void Enemy::DirCheck()
{
	if (Type == EnemyType::WallTurret)
	{
		return;
	}

	float4 DirDeg = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

	if (DirDeg.Angle2DDeg() > 90.0f && DirDeg.Angle2DDeg() < 270.0f)
	{
		Dir = EnemyDir::Left;
		EnemyMainRenderer->LeftFlip();
		EnemyEffectRenderer->LeftFlip();
		EnemyDetectCollision->Transform.SetLocalPosition({ -170.0f, 0.0f });
		return;
	}
	else
	{
		Dir = EnemyDir::Right;
		EnemyMainRenderer->RightFlip();
		EnemyEffectRenderer->RightFlip();
		EnemyDetectCollision->Transform.SetLocalPosition({ 170.0f, 0.0f });
		return;
	}

}

void Enemy::ResetDir()
{
	if (Type == EnemyType::WallTurret)
	{
		return;
	}

	if (InitDir == EnemyDir::Left)
	{
		EnemyMainRenderer->LeftFlip();
		EnemyEffectRenderer->LeftFlip();
		EnemyDetectCollision->Transform.SetLocalPosition({ -170.0f, 0.0f });
		return;
	}
	else
	{
		EnemyMainRenderer->RightFlip();
		EnemyEffectRenderer->RightFlip();
		EnemyDetectCollision->Transform.SetLocalPosition({ 170.0f, 0.0f });
		return;
	}
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

	EnemyEmotionRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	EnemyEmotionRenderer->SetSprite("spr_enemy_question.png");
	EnemyEmotionRenderer->AutoSpriteSizeOn();

	EnemyEmotionRenderer->Transform.SetLocalPosition({ 0.0f, 42.0f, 0.0f, 1.0f });
	EnemyEmotionRenderer->Off();

}

void Enemy::Update(float _Delta)
{

	if (Type != EnemyType::WallTurret)
	{
		Gravity(_Delta);

		if (true == GetGroundPixelCollision())
		{
			CheckPos = { Transform.GetWorldPosition() + DownCheck };

			GameEngineColor Color = GetMapColor(CheckPos, GameEngineColor::WHITE);


			if (Color == GameEngineColor::RED)
			{
				Transform.AddWorldPosition(float4::UP * _Delta * Speed);
			}
		}
	}

	if (true == GameStateManager::GameState->GetCurrentGameClear())
	{
		RecordPlayModeOn();
		Replay();
		return;
	}

	else if (true == GameStateManager::GameState->GetCurrentGameState())
	{
		RecordPlayModeOn();
		Reverse(_Delta);
		return;
	}

	else
	{
		RecordPlayModeOff();
		EnemyDamagedEvent(_Delta);
	}

	if (true == IsUsingAutoPattern)
	{
		FSM_EnemyState.Update(_Delta);
	}

	if (true == ActorInfo.empty() && true == RendererInfo.empty() && Type != EnemyType::WallTurret)
	{
		IsEnemyDeath = false;
		FSM_EnemyState.ChangeState(FSM_EnemyState::Idle);
	}

	UpdateAddingRecordData(_Delta);

}

void Enemy::EnemyDamagedEvent(float _Delta)
{
	EventParameter Event;

	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(thisActor);

		std::shared_ptr<PlayerCursorSlash> NewPlayerSlash = GetLevel()->CreateActor<PlayerCursorSlash>(static_cast<int>(ContentsRenderType::Play));

		std::shared_ptr<Fx> NewSlashFx = EnemyPtr->GetLevel()->CreateActor<Fx>();
		NewSlashFx->SetFxData(EFx_Type::Slash, float4::ZERO);
		NewSlashFx->Transform.SetLocalPosition(EnemyPtr->Transform.GetWorldPosition());


		EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
		return;
	};

	Event.Stay = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* PlayerAttackActor = Col->GetActor();

		static float Timer = 0.0f;

		Timer += _Delta;

		if (Timer > 0.1f && PlayerAttackActor != nullptr)
		{
			Col->Death();
		}
	};

	EnemyMainCollision->CollisionEvent(ContentsCollisionType::PlayerAttack, Event);
}

void Enemy::EnemyPlayerDetectEvent()
{
	// Enemy가 Player를 감지하면 이모지가 바뀌고, 추격을 시작한다.
	// 충돌 범위를 벗어나면 이 상태는 해제 된다.

	// ★ 플레이어와 다른 층에 있는 Enemy가 플레이어를 감지하면 층을 이동하면서 추격한다.

	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(thisActor);

		if (true == EnemyPtr->IsDetectDoor)
		{
			return;
		}

		if (EnemyPtr->Type != EnemyType::FloorTurret && EnemyPtr->Type != EnemyType::WallTurret)
		{
			EnemyPtr->ChangeEmotion(EEnemyState_Emotion::NormalExclamation);
			EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Chase);
			return;
		}
		else
		{
			EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
			return;
		}


	};

	Event.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(thisActor);

		if (true == EnemyPtr->IsDetectDoor)
		{
			return;
		}

		if (EnemyPtr->Type != EnemyType::FloorTurret && EnemyPtr->Type != EnemyType::WallTurret)
		{
			EnemyPtr->ChangeEmotion(EEnemyState_Emotion::HardExclamation);
			EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Chase);
			return;
		}
		else
		{
			EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Attack);
			return;
		}



	};

	Event.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(thisActor);

		EnemyPtr->ChangeEmotion(EEnemyState_Emotion::Default);
		return;
	};

	EnemyDetectCollision->CollisionEvent(ContentsCollisionType::PlayerBody, Event);
}