#include "PreCompile.h"
#include "Boss.h"
#include "Player.h"
#include "WallOpen.h"
#include "BossGrenade.h"
#include "Item.h"
#include "FX_Explosion.h"
#include "GameStateManager.h"

Boss* Boss::Boss_HeadHunter = nullptr;
Boss::Boss()
{
	Boss_HeadHunter = this;
}

Boss::~Boss()
{
}

void Boss::DirCheck()
{
	float4 DirDeg = Player::MainPlayer->Transform.GetWorldPosition() - Transform.GetWorldPosition();

	if (DirDeg.Angle2DDeg() > 90.0f && DirDeg.Angle2DDeg() < 270.0f)
	{
		Dir = BossDir::Left;
		BossMainRenderer->LeftFlip();
		return;
	}
	else
	{
		Dir = BossDir::Right;
		BossMainRenderer->RightFlip();
		return;
	}
}

void Boss::Start()
{
	GameEngineInput::AddInputObject(this);

#pragma region 렌더러 & 애니메이션 세팅


	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_BossAutoText.png"));
			GameEngineSprite::CreateSingle("UI_BossAutoText.png");
		}
	}

	DebugRenderer_Auto = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	DebugRenderer_Auto->SetSprite("UI_BossAutoText.png");
	DebugRenderer_Auto->Transform.SetLocalPosition({ 0, 60.0f });
	DebugRenderer_Auto->AutoSpriteSizeOn();
	DebugRenderer_Auto->Off();

	BossMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossMainRenderer->AutoSpriteSizeOn();

	BossMainRenderer->CreateAnimation("Idle", "spr_headhunter_idle");

	BossMainRenderer->CreateAnimation("PutBackRifle", "spr_headhunter_putbackrifle", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("AimRifle_180", "spr_headhunter_aim_rifle_180");
	BossMainRenderer->CreateAnimation("AimRifle_170", "spr_headhunter_aim_rifle_170");
	BossMainRenderer->CreateAnimation("AimRifle_160", "spr_headhunter_aim_rifle_160");
	BossMainRenderer->CreateAnimation("AimRifle_150", "spr_headhunter_aim_rifle_150");
	BossMainRenderer->CreateAnimation("AimRifle_140", "spr_headhunter_aim_rifle_140");
	BossMainRenderer->CreateAnimation("AimRifle_130", "spr_headhunter_aim_rifle_130");
	BossMainRenderer->CreateAnimation("AimRifle_120", "spr_headhunter_aim_rifle_120");
	BossMainRenderer->CreateAnimation("AimRifle_110", "spr_headhunter_aim_rifle_110");
	BossMainRenderer->CreateAnimation("AimRifle_100", "spr_headhunter_aim_rifle_100");
	BossMainRenderer->CreateAnimation("AimRifle_90", "spr_headhunter_aim_rifle_90");
	BossMainRenderer->CreateAnimation("TakeOutRifle", "spr_headhunter_takeoutrifle", 0.02f, 0, 7, false);

	BossMainRenderer->CreateAnimation("Shoot", "spr_headhunter_shoot", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("PutBackGun", "spr_headhunter_putbackgun", 0.1f, 0, 6, false);
	BossMainRenderer->CreateAnimation("TakeOutGun", "spr_headhunter_takeoutgun", 0.1f, 0, 6, false);

	BossMainRenderer->CreateAnimation("TeleportOut", "spr_headhunter_teleport_out", 0.1f, 0, 3, false);
	BossMainRenderer->CreateAnimation("TeleportIn", "spr_headhunter_teleport_in", 0.1f, 0, 3, false);

	BossMainRenderer->CreateAnimation("Sweep", "spr_headhunter_sweep", 0.123f, 0, 17, false);
	BossMainRenderer->CreateAnimation("SweepTeleportOut", "spr_headhunter_teleport_out_sweep", 0.1f, 0, 2, false);
	BossMainRenderer->CreateAnimation("SweepTeleportIn", "spr_headhunter_teleport_in_sweep", 0.1f, 0, 3, false);

	BossMainRenderer->CreateAnimation("PreDash", "spr_headhunter_predash", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("Dash", "spr_headhunter_dash");
	BossMainRenderer->CreateAnimation("DashEnd", "spr_headhunter_dash_end_ground", 0.1f, 0, 9, false);

	BossMainRenderer->CreateAnimation("WallIdle", "spr_headhunter_wall_idle", 0.1f, 0, 2, false);
	BossMainRenderer->CreateAnimation("WallJump", "spr_headhunter_walljump", 0.25f, 0, 6, false);
	BossMainRenderer->CreateAnimation("WallLand", "spr_headhunter_walljump_land", 0.1f, 0, 3, false);

	BossMainRenderer->CreateAnimation("RevealBomb", "spr_headhunter_reveal_bomb", 0.1f, 0, 7, false);
	BossMainRenderer->CreateAnimation("BombRun", "spr_headhunter_bomb_run");

	BossMainRenderer->CreateAnimation("DodgeRoll", "spr_headhunter_dodgeroll", 0.1f, 0, 6, false);

	BossMainRenderer->CreateAnimation("Hurt", "spr_headhunter_hurt", 0.2f, 0, 9, false);
	BossMainRenderer->CreateAnimation("DieLand", "spr_headhunter_dieland", 0.2f, 0, 7, false);
	BossMainRenderer->CreateAnimation("Crawl", "spr_headhunter_dead");
	BossMainRenderer->CreateAnimation("Death", "spr_headhunter_nohead", 0.1f, 0, 5, false);

	BossMainRenderer->CreateAnimation("Fall", "spr_headhunter_jump", 0.1f, 0, 0, true);



	BossMainRenderer->CreateAnimation("Exit", "spr_headhunter_exit_door", 0.1f, 0, 2, false);
	BossMainRenderer->CreateAnimation("TeleportInGround", "spr_headhunter_teleport_in_ground", 0.1f, 0, 3, false);
	BossMainRenderer->CreateAnimation("TeleportOutGround", "spr_headhunter_teleport_out_ground", 0.1f, 0, 3, false);

	

	BossMainRenderer->ChangeAnimation("Idle");

	BossMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::EnemyBody);
	BossMainCollision->Transform.SetLocalScale({ 30, 30, 1 });
	BossMainCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });

	// 역 재생용 렌더러 세팅
	AddRecordingRenderer(BossMainRenderer);

#pragma endregion

#pragma region FSM 등록

	FSM_Boss_Idle();

	FSM_Boss_GroundRifleAttack();
	FSM_Boss_GroundRifleAttackEnd();

	FSM_Boss_AirRifleAttack_Start();
	FSM_Boss_AirRifleAttack();
	FSM_Boss_AirRifleAttackEnd();

	FSM_Boss_MultipleAirRifleAttack();

	FSM_Boss_GroundDashAttack();
	FSM_Boss_AirDashAttack();

	FSM_Boss_WallJump_Start();
	FSM_Boss_WallJump();
	FSM_Boss_WallJump_End();

	FSM_Boss_GrenadeAttack_Start();
	FSM_Boss_GrenadeAttack();
	FSM_Boss_GrenadeAttack_End();

	FSM_Boss_WallTurretAttack();

	FSM_Boss_SuicideBombingAttack_Start();
	FSM_Boss_SuicideBombingAttack();

	FSM_Boss_DodgeRoll();

	FSM_Boss_Hurt();

	FSM_Boss_Fall();
	FSM_Boss_DieLand();
	FSM_Boss_Death();
	FSM_Boss_Crawl();

	FSM_Boss_TeleportInGround();
	FSM_Boss_TeleportOutGround();

	SetCharacterType(CharacterType::Boss);
	FSM_BossState.ChangeState(FSM_BossState::Idle);
#pragma endregion

#pragma region FX Sound 파일 로딩

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
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\FX\\EnemyFX\\BossFX\\");

		if (nullptr == GameEngineSound::FindSound("sound_boss_hurt1.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_boss_hurt1.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_boss_lasershot_swipe.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_boss_lasershot_swipe.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_boss_lasershot_vertical.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_boss_lasershot_vertical.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_boss_lasershot.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_boss_lasershot.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_boss_gatling.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_boss_gatling.wav"));
		}

	}

#pragma endregion

}

void Boss::Update(float _Delta)
{

	if (GameEngineInput::IsDown('U', this))
	{
		if (true == IsUsingAutoPattern)
		{
			IsUsingAutoPattern = false;

			if (true == DebugRenderer_Auto->GetUpdateValue())
			{
				DebugRenderer_Auto->Off();
			}
		}
		else
		{
			IsUsingAutoPattern = true;

			if (false == DebugRenderer_Auto->GetUpdateValue())
			{
				DebugRenderer_Auto->On();
			}
		}
	}

	/*GameEngineDebug::DrawLine(Transform.GetWorldPosition(), { Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y + 500.0f }, float4::GREEN);*/
	
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

		if (false == BossMainRenderer->GetUpdateValue())
		{
			SetBossActivate();
		}

		if (WallTurretObject != nullptr)
		{
			WallTurretObject->ResetWall();
		}

		return;
	}

	else
	{
		RecordPlayModeOff();
		BossDamagedEvent();
		BossSelfDamagedEvent();
	}

	if (false == Player::MainPlayer->IsDeath)
	{
		FSM_BossState.Update(_Delta);
	}

	UpdateAddingRecordData(_Delta);
}

void Boss::SpawnWallTurretEvent(GameEngineRenderer* _Renderer)
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	WallTurretObject = GetLevel()->CreateActor<WallOpen>();
	WallTurretObject->Transform.SetLocalPosition({ HalfWindowScale.X - 468.0f, -HalfWindowScale.Y - 30.0f });
}

void Boss::ResetEvent(GameEngineRenderer* _Renderer)
{

}

void Boss::BossDamagedEvent()
{
	EventParameter Event;

	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Boss* BossPtr = dynamic_cast<Boss*>(thisActor);

		GameEngineActor* PlayerAttackActor = Col->GetActor();
		Col->Death();

		if (3 == BossPtr->GetBossHp())
		{
			BossPtr->BossMainRenderer->SetFrameEvent("Hurt", 9, std::bind(&Boss::SpawnWallTurretEvent, BossPtr, std::placeholders::_1));
			BossPtr->FSM_BossState.ChangeState(FSM_BossState::Hurt);
			BossPtr->SetBossHp(2);
			return;
		}

		if (2 == BossPtr->GetBossHp())
		{
			BossPtr->BossMainRenderer->SetFrameEvent("Hurt", 9, std::bind(&Boss::ResetEvent, BossPtr, std::placeholders::_1));
			BossPtr->FSM_BossState.ChangeState(FSM_BossState::Hurt);
			BossPtr->SetBossHp(1);
			return;
		}

		if (1 == BossPtr->GetBossHp())
		{
			KnifeItem = GetLevel()->CreateActor<Item>();
			KnifeItem->SetItemData(EItemType::Knife);
			KnifeItem->Transform.SetLocalPosition(Transform.GetLocalPosition());

			BossPtr->FSM_BossState.ChangeState(FSM_BossState::Hurt);
			BossPtr->SetBossHp(0);
			return;
		}

		if (0 == BossPtr->GetBossHp())
		{
			BossPtr->SetBossHp(-1);

			GameEngineRandom Random;

			// FX 생성 위치 랜덤 설정
			for (int i = 0; i < 50; i++)
			{
				int RandomPosX = Random.RandomInt(-110, 110);
				int RandomPosY = Random.RandomInt(-80, 80);

				std::shared_ptr<FX_Explosion> EnemyNewBullet = GetLevel()->CreateActor<FX_Explosion>(static_cast<int>(ContentsRenderType::Play));
				EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + RandomPosX, Transform.GetLocalPosition().Y + RandomPosY });
			}

			FSM_BossState.ChangeState(FSM_BossState::DieLand);
			return;
		}


		if (-1 <= BossPtr->GetBossHp())
		{
			BossPtr->FSM_BossState.ChangeState(FSM_BossState::Death);
			return;
		}

	};

	BossMainCollision->CollisionEvent(ContentsCollisionType::PlayerAttack, Event);
}

void Boss::BossSelfDamagedEvent()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Boss* BossPtr = dynamic_cast<Boss*>(thisActor);

		GameEngineActor* GrenadeAttackActor = Col->GetActor();
		BossGrenade* BossGrenadePtr = dynamic_cast<BossGrenade*>(GrenadeAttackActor);
		Col->Death();

		if (/*BossGrenadePtr != nullptr && */true == BossGrenadePtr->GetSelfAttackable())
		{
			if (3 == BossPtr->GetBossHp())
			{
				BossPtr->BossMainRenderer->SetFrameEvent("Hurt", 9, std::bind(&Boss::SpawnWallTurretEvent, BossPtr, std::placeholders::_1));
				BossPtr->FSM_BossState.ChangeState(FSM_BossState::Hurt);
				BossPtr->SetBossHp(2);
				return;
			}
		}

	};

	BossMainCollision->CollisionEvent(ContentsCollisionType::BossGrenadeArea, Event);

}

void Boss::BossDashAttackFromPlayerEvent()
{
	EventParameter Event;

	Event.Enter = [=](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		//GameEngineActor* thisActor = _this->GetActor();
		//Boss* BossPtr = dynamic_cast<Boss*>(thisActor);

		//GameEngineActor* PlayerAttackActor = Col->GetActor();
		//Col->Death();

		//if (3 == BossPtr->GetBossHp())
		//{
		//	BossPtr->BossMainRenderer->SetFrameEvent("Hurt", 9, std::bind(&Boss::SpawnWallTurretEvent, BossPtr, std::placeholders::_1));
		//	BossPtr->FSM_BossState.ChangeState(FSM_BossState::Hurt);
		//	BossPtr->SetBossHp(2);
		//	return;
		//}

		//if (2 == BossPtr->GetBossHp())
		//{
		//	BossPtr->BossMainRenderer->SetFrameEvent("Hurt", 9, std::bind(&Boss::ResetEvent, BossPtr, std::placeholders::_1));
		//	BossPtr->FSM_BossState.ChangeState(FSM_BossState::Hurt);
		//	BossPtr->SetBossHp(1);
		//	return;
		//}

		//if (1 == BossPtr->GetBossHp())
		//{
		//	KnifeItem = GetLevel()->CreateActor<Item>();
		//	KnifeItem->SetItemData(EItemType::Knife);
		//	KnifeItem->Transform.SetLocalPosition(Transform.GetLocalPosition());

		//	BossPtr->FSM_BossState.ChangeState(FSM_BossState::Hurt);
		//	BossPtr->SetBossHp(0);
		//	return;
		//}

		//if (0 == BossPtr->GetBossHp())
		//{
		//	BossPtr->SetBossHp(-1);

		//	GameEngineRandom Random;

		//	// FX 생성 위치 랜덤 설정
		//	for (int i = 0; i < 50; i++)
		//	{
		//		int RandomPosX = Random.RandomInt(-110, 110);
		//		int RandomPosY = Random.RandomInt(-80, 80);

		//		std::shared_ptr<FX_Explosion> EnemyNewBullet = GetLevel()->CreateActor<FX_Explosion>(static_cast<int>(ContentsRenderType::Play));
		//		EnemyNewBullet->Transform.SetLocalPosition({ Transform.GetLocalPosition().X + RandomPosX, Transform.GetLocalPosition().Y + RandomPosY });
		//	}

		//	FSM_BossState.ChangeState(FSM_BossState::DieLand);
		//	return;
		//}


		//if (-1 <= BossPtr->GetBossHp())
		//{
		//	BossPtr->FSM_BossState.ChangeState(FSM_BossState::Death);
		//	return;
		//}

	};

	BossMainCollision->CollisionLineEvent(ContentsCollisionType::PlayerDash, Player::MainPlayer->End, Event);
}

