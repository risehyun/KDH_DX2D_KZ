#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Enemy.h"
#include "ContentsEnum.h"

#include "PlayerAttack.h"
#include "UI_Mouse.h"
#include "GameStateManager.h"
#include "BossGrenade.h"

#include "ThrowingAttack.h"
#include "UI_PlayUI.h"
#include "Boss.h"

Player* Player::MainPlayer = nullptr;
Player::Player()
{
	MainPlayer = this;
	SetCharacterType(CharacterType::Player);
}

Player::~Player()
{
}

void Player::Start()
{

	// 입력 가능 오브젝트로 등록
	GameEngineInput::AddInputObject(this);

#pragma region 충돌체 설정
	PlayerBodyCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerBody);
	PlayerBodyCollision->Transform.SetLocalScale({ 30, 30, 1 });
	PlayerBodyCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });

	PlayerParryingCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerParrying);
	PlayerParryingCollision->Transform.SetLocalScale({ 300, 100, 1 });
	PlayerParryingCollision->Transform.SetLocalPosition({ 0.0f, 0.0f, 1.0f });

	PlayerDashCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerDash);
	PlayerDashCollision->SetCollisionType(ColType::LINE2D);
#pragma endregion

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}



	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		MainSpriteRenderer->CreateAnimation("Idle", "spr_dragon_idle");

		MainSpriteRenderer->CreateAnimation("IdleToRun", "spr_dragon_idle_to_run", 0.1f, 0, 2, false);
		MainSpriteRenderer->CreateAnimation("RunToIdle", "spr_dragon_run_to_idle", 0.1f, 0, 3, false);

		MainSpriteRenderer->CreateAnimation("Run", "spr_dragon_run");
		MainSpriteRenderer->CreateAnimation("Jump", "spr_dragon_jump");
		MainSpriteRenderer->CreateAnimation("Fall", "spr_dragon_fall");
		MainSpriteRenderer->CreateAnimation("Roll", "spr_dragon_roll");
		MainSpriteRenderer->CreateAnimation("Attack", "spr_dragon_attack");
		MainSpriteRenderer->CreateAnimation("Dash", "spr_dragon_dash");
		MainSpriteRenderer->CreateAnimation("Death", "spr_dragon_hurtground", 0.1f, 0, 5, false);

		MainSpriteRenderer->CreateAnimation("DoorKick", "spr_dragon_doorkick", 0.1f, 2, 5, true);
		MainSpriteRenderer->CreateAnimation("PreCrouch", "spr_dragon_PreCrouch", 0.1f, 0, 1, false);
		MainSpriteRenderer->CreateAnimation("Postcrouch", "spr_dragon_postcrouch", 0.1f, 0, 1, false);
		MainSpriteRenderer->AutoSpriteSizeOn();

	}

	{
		PlayerFXRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		PlayerFXRenderer->CreateAnimation("JumpCloud", "spr_player_jumpcloud", 0.1f, 0, 3, false);
		PlayerFXRenderer->CreateAnimation("LandCloud", "spr_player_landcloud", 0.1f, 0, 6, false);
		PlayerFXRenderer->CreateAnimation("RunCloud", "spr_player_dustcloud", 0.1f, 0, 6, true);


		PlayerFXRenderer->AutoSpriteSizeOn();
		PlayerFXRenderer->Transform.SetLocalPosition({ 0.0f, -10.0f, 0.0f, 1.0f });
		PlayerFXRenderer->Off();
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_dragon_dash_range.png"));
			GameEngineSprite::CreateSingle("spr_dragon_dash_range.png");
		}
	}

	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_PlayerImmoralModeText.png"));
			GameEngineSprite::CreateSingle("UI_PlayerImmoralModeText.png");
		}
	}

	DebugRenderer_Immortal = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	DebugRenderer_Immortal->SetSprite("UI_PlayerImmoralModeText.png");
	DebugRenderer_Immortal->Transform.SetLocalPosition({ 0, 60.0f });
	DebugRenderer_Immortal->AutoSpriteSizeOn();
	DebugRenderer_Immortal->Off();


	PlayerRenderer_Dash = CreateComponent<GameEngineSpriteRenderer>(30);
	PlayerRenderer_Dash->SetSprite("spr_dragon_dash_range.png");
	PlayerRenderer_Dash->Transform.SetLocalPosition({ 0, 0 });
	PlayerRenderer_Dash->AutoSpriteSizeOn();
	PlayerRenderer_Dash->Off();




#pragma region FX Sound 리소스 파일 열기
	// Fx Sound 파일
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\FX\\PlayerFX\\");

		if (nullptr == GameEngineSound::FindSound("sound_player_jump.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_jump.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_land.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_land.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_running_1.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_1.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_running_2.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_2.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_running_3.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_3.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_running_4.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_running_4.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_slash_1.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_slash_1.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_slash_2.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_slash_2.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_slash_3.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_slash_3.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_bulletparry_slash.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_bulletparry_slash.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_roll.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_roll.wav"));
		}

		if (nullptr == GameEngineSound::FindSound("sound_player_death.wav"))
		{
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("sound_player_death.wav"));
		}

	}
#pragma endregion





	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("UI_ReverseText.png"));
			GameEngineSprite::CreateSingle("UI_ReverseText.png");
		}

		DebugRenderer_Reverse = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		DebugRenderer_Reverse->SetSprite("UI_ReverseText.png");
		DebugRenderer_Reverse->Transform.SetLocalPosition({ 0.0f, 40.0f });
		DebugRenderer_Reverse->Off();
	}

	{
		//// 충돌 디버그용 렌더러
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("Test.bmp"));
			GameEngineSprite::CreateSingle("Test.bmp");

			GameEngineTexture::Load(FilePath.PlusFilePath("spr_cursor_slash.png"));
			GameEngineSprite::CreateSingle("spr_cursor_slash.png");

			GameEngineTexture::Load(FilePath.PlusFilePath("DashLine.png"));
			GameEngineSprite::CreateSingle("DashLine.png");
		}

		PlayerRenderer_DashLine = CreateComponent<GameEngineSpriteRenderer>(30);
		PlayerRenderer_DashLine->AutoSpriteSizeOn();
		PlayerRenderer_DashLine->SetSprite("DashLine.png");


	/*	std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Left = CreateComponent<GameEngineSpriteRenderer>(30);
		DebugRenderer_Left->AutoSpriteSizeOn();
		DebugRenderer_Left->SetSprite("Test.bmp");
		DebugRenderer_Left->Transform.SetLocalPosition(LeftDownCheck);

		std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Right = CreateComponent<GameEngineSpriteRenderer>(30);
		DebugRenderer_Right->AutoSpriteSizeOn();
		DebugRenderer_Right->SetSprite("Test.bmp");
		DebugRenderer_Right->Transform.SetLocalPosition(LeftUpCheck);

		std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Up = CreateComponent<GameEngineSpriteRenderer>(30);
		DebugRenderer_Up->AutoSpriteSizeOn();
		DebugRenderer_Up->SetSprite("Test.bmp");
		DebugRenderer_Up->Transform.SetLocalPosition(UpCheck);

		std::shared_ptr<GameEngineSpriteRenderer> DebugRenderer_Down = CreateComponent<GameEngineSpriteRenderer>(30);
		DebugRenderer_Down->AutoSpriteSizeOn();
		DebugRenderer_Down->SetSprite("Test.bmp");
		DebugRenderer_Down->Transform.SetLocalPosition(DownCheck);*/

	}

	// 역 재생용 렌더러 세팅
	AddRecordingRenderer(MainSpriteRenderer);


	// FSM 등록
	FSM_Player_Idle();
	FSM_Player_PreCrouch();
	FSM_Player_Roll();
	FSM_Player_Jump();
	FSM_Player_Fall();
	FSM_Player_Run();
	FSM_Player_Dash();
	FSM_Player_Attack();
	FSM_Player_DoorKick();
	FSM_Player_RunToIdle();
	FSM_Player_IdleToRun();
	FSM_Player_Death();

	FSM_PlayerState.ChangeState(FSM_PlayerState::Idle);
}

// 재생 -> FSM 업데이트 -> 재생 데이터 순서 고정 유의
void Player::Update(float _Delta)
{

	// 무적모드 사용
	if (GameEngineInput::IsDown('I', this))
	{
		if (true == IsImmortal)
		{
			IsImmortal = false;

			if (true == DebugRenderer_Immortal->GetUpdateValue())
			{
				DebugRenderer_Immortal->Off();
			}
		}
		else
		{
			IsImmortal = true;

			if (false == DebugRenderer_Immortal->GetUpdateValue())
			{
				DebugRenderer_Immortal->On();
			}
		}
	}

	if (GameEngineInput::IsDown('X', this))
	{
		FSM_PlayerState.ChangeState(FSM_PlayerState::Death);
		return;
	}

	if (true == GameStateManager::GameState->GetCurrentGameClear())
	{
		RecordPlayModeOn();
		Replay();
		return;
	}

	else if (true == GameStateManager::GameState->GetCurrentGameState())
	{
	//	DebugRenderer_Reverse->On();
		RecordPlayModeOn();
		Reverse(_Delta);
		return;
	}

	else
	{
		RecordPlayModeOff();
	//	DebugRenderer_Reverse->Off();
		Update_PlayerDashCoolTime(_Delta);
		PlayerBossGrenadeDamagedEvent();
		PlayerBossParryEvent();
		PlayerParryEvent();
		PlayerDamagedEvent();
		PlayerBossAttackKnockBackEvent();
	}

	if (true == ActorInfo.empty() && true == RendererInfo.empty())
	{
		if (nullptr != PlayerBodyCollision && false == PlayerBodyCollision->GetUpdateValue())
		{
			PlayerBodyCollision->On();
		}

	}

	FSM_PlayerState.Update(_Delta);

	UpdateAddingRecordData(_Delta);

}

void Player::DirCheck()
{
	// 방향을 결정하는 키들이 모두 프리라면 그상태 그대로 유지. 아래의 D가 프리일때 Left가 되는 것을 방지.
	if (GameEngineInput::IsFree('A', this) && true == GameEngineInput::IsFree('D', this))
	{
		return;
	}

	// A가 눌렸거나 D가 프리이라면 Left로 방향전환 인데 가만히있어도 Left를 바라보는 현상이 생김.
	if (GameEngineInput::IsDown('A', this) || GameEngineInput::IsFree('D', this))
	{
		Dir = PlayerDir::Left;
		SetPlayerDir(Dir);
		MainSpriteRenderer->LeftFlip();
		return;
	}

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
	if (GameEngineInput::IsDown('D', this) || GameEngineInput::IsFree('A', this))
	{
		Dir = PlayerDir::Right;
		SetPlayerDir(Dir);
		MainSpriteRenderer->RightFlip();
		return;
	}
}

void Player::PlayerBossGrenadeDamagedEvent()
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* GrenadeAttackActor = Col->GetActor();
		BossGrenade* BossGrenadePtr = dynamic_cast<BossGrenade*>(GrenadeAttackActor);
		
		if (Col != nullptr && true == Col->GetUpdateValue())
		{
			Col->Death();
		}

		if (true == Player::MainPlayer->IsImmortal)
		{
			return;
		}

		if (Player::MainPlayer->GetMainRenderer()->IsCurAnimation("Death"))
		{
			return;
		}

		else if (false == BossGrenadePtr->GetSelfAttackable())
		{
			Player::MainPlayer->FSM_PlayerState.ChangeState(FSM_PlayerState::Death);
			return;
		}

	};

	PlayerBodyCollision->CollisionEvent(ContentsCollisionType::BossGrenadeArea, Event);

}

void Player::PlayerDamagedEvent()
{
	EventParameter BodyCollisionEvent;

	BodyCollisionEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		if (true == PlayerPtr->IsImmortal)
		{
			return;
		}

		PlayerPtr->FSM_PlayerState.ChangeState(FSM_PlayerState::Death);

		GameEngineActor* EnemyAttackActor = Col->GetActor();
		EnemyAttackActor->Death();
	};

	PlayerBodyCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, BodyCollisionEvent);
}

void Player::PlayerParryEvent()
{
	EventParameter ParryCollisionEvent;

	ParryCollisionEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		PlayerPtr->OnParryable();

	};

	ParryCollisionEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

		GameEngineActor* thisActor = _this->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		PlayerPtr->OffParryable();

	};

	PlayerParryingCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, ParryCollisionEvent);
}

void Player::PlayerBossParryEvent()
{
	EventParameter ParryCollisionEvent;

	ParryCollisionEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		PlayerPtr->OnParryable();

	};

	ParryCollisionEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

		GameEngineActor* thisActor = _this->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		PlayerPtr->OffParryable();

	};

	PlayerParryingCollision->CollisionEvent(ContentsCollisionType::BossGrenade, ParryCollisionEvent);
}

void Player::PlayerDashAttackEvent()
{
	EventParameter DashCollisionEvent;

	DashCollisionEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

		GameEngineActor* EnemyActor = Col->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(EnemyActor);

		if (true == EnemyPtr->IsEnemyDeath)
		{
			return;
		}

		EnemyPtr->FSM_EnemyState.ChangeState(FSM_EnemyState::Death);
		return;

	};

	PlayerDashCollision->CollisionLineEvent(ContentsCollisionType::EnemyBody, End, DashCollisionEvent);

}


void Player::PlayerBossAttackKnockBackEvent()
{
	EventParameter BossAttackKnockBackEvent;

	BossAttackKnockBackEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

		if (PlayerPtr->Dir == PlayerDir::Left)
		{
			PlayerPtr->Transform.AddLocalPosition(float4::RIGHT * GameEngineCore::MainTime.GetDeltaTime() * PlayerPtr->Speed);
		}
		else if (PlayerPtr->Dir == PlayerDir::Right)
		{
			PlayerPtr->Transform.AddLocalPosition(float4::LEFT * GameEngineCore::MainTime.GetDeltaTime() * PlayerPtr->Speed);
		}
	};

	BossAttackKnockBackEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

	};

	PlayerBodyCollision->CollisionEvent(ContentsCollisionType::BossGrenade, BossAttackKnockBackEvent);

}

void Player::Update_PlayerDashCoolTime(float _Delta)
{
	if (true == IsOnDashCoolTimeDecrease)
	{
		if (CurPlayerDashCoolTime <= MaxPlayerDashCoolTime)
		{
			CurPlayerDashCoolTime += _Delta;

			if (CurPlayerDashCoolTime > MaxPlayerDashCoolTime)
			{
				CurPlayerDashCoolTime = 0.0f;
				IsOnDashCoolTimeDecrease = false;
			}
		}
	}
}