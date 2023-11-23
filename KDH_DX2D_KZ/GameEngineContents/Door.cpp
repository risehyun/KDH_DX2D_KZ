#include "PreCompile.h"
#include "Door.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"
#include "Enemy.h"
#include "GameStateManager.h"

Door::Door()
{

}

Door::~Door()
{
}

void Door::SetDoorData(EDoorType _Type, DoorDir _Dir)
{
	Type = _Type;
	Dir = _Dir;

	if (Type == EDoorType::Normal)
	{

		DoorMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));

		DoorMainRenderer->CreateAnimation("DoorIdle", "spr_door_animation", 0.1f, 0, 0, true);
		DoorMainRenderer->CreateAnimation("DoorOpen", "spr_door_animation", 0.01f, 1, 19, false);

		DoorMainRenderer->AutoSpriteSizeOn();

		DoorMainRenderer->ChangeAnimation("DoorIdle");
	}

	else if (Type == EDoorType::Iron)
	{

		DoorMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));

		DoorMainRenderer->CreateAnimation("DoorIdle", "spr_door_animation_iron", 0.1f, 0, 0, true);
		DoorMainRenderer->CreateAnimation("DoorOpen", "spr_door_animation_iron", 0.01f, 1, 19, false);

		DoorMainRenderer->AutoSpriteSizeOn();

		DoorMainRenderer->ChangeAnimation("DoorIdle");
	}

	if (Dir == DoorDir::Left)
	{
		DoorMainRenderer->LeftFlip();
		DoorGlowRenderer->LeftFlip();
		DoorMainCollision->Transform.SetLocalPosition({ 100.0f });
	}

	else
	{
		DoorMainRenderer->RightFlip();
		DoorGlowRenderer->RightFlip();
		DoorMainCollision->Transform.SetLocalPosition({ -100.0f });
	}

	// 역 재생용 렌더러 세팅
	AddRecordingRenderer(DoorMainRenderer);
	AddRecordingRenderer(DoorGlowRenderer);
}

void Door::Start()
{
	GameEngineInput::AddInputObject(this);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	DoorGlowRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::BackGround));
	DoorGlowRenderer->CreateAnimation("DoorGlow1", "spr_door_glow", 0.1f, 0, 0, false);
	DoorGlowRenderer->AutoSpriteSizeOn();
	DoorGlowRenderer->ChangeAnimation("DoorGlow1");

	DoorMainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	DoorMainCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Door::Update(float _Delta)
{

	if (true == GameStateManager::GameState->GetCurrentGameClear())
	{
		RecordPlayModeOn();
		Replay();
		return;
	}

	else if (true == GameStateManager::GameState->GetCurrentGameState())
	{
		RecordPlayModeOn();
		Reverse();
		return;
	}

	else
	{
		RecordPlayModeOff();
	}

	UpdateAddingRecordData(_Delta);


	DoorAutoOpenEvent();
	DoorAttackOpenEvent();
	DoorDetectEnemyEvent();
}

void Door::DoorAutoOpenEvent()
{
	EventParameter DoorAutoOpenEvent;

	DoorAutoOpenEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

	};

	DoorAutoOpenEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* PlayerActor = Col->GetActor();
		Player* PlayerPtr = dynamic_cast<Player*>(PlayerActor);

		GameEngineActor* thisActor = _this->GetActor();
		Door* DoorPtr = dynamic_cast<Door*>(thisActor);

		if (DoorPtr->Dir == DoorDir::Right)
		{
			// ★ 문제 생길 수 있음
			if (true == GameEngineInput::IsPress('D', thisActor))
			{
				DoorPtr->DoorPushTimer += GameEngineCore::MainTime.GetDeltaTime();

				if (DoorPtr->DoorPushTimer > 0.1f)
				{

					for (size_t i = 0; i < DoorPtr->DetectedEnemy.size(); i++)
					{
						DoorPtr->DetectedEnemy[i]->IsDetectDoor = false;
					}

					DoorPtr->DoorMainRenderer->ChangeAnimation("DoorOpen");
					DoorPtr->DoorGlowRenderer->Off();
					DoorPtr->DoorMainCollision->Off();

					PlayerPtr->FSM_PlayerState.ChangeState(FSM_PlayerState::DoorKick);
					return;
				}
			}
		}

		else if (DoorPtr->Dir == DoorDir::Left)
		{

			// ★ 문제 생길 수 있음
			if (true == GameEngineInput::IsPress('A', thisActor))
			{
				DoorPtr->DoorPushTimer += GameEngineCore::MainTime.GetDeltaTime();

				if (DoorPtr->DoorPushTimer > 0.1f)
				{

					for (size_t i = 0; i < DoorPtr->DetectedEnemy.size(); i++)
					{
						DoorPtr->DetectedEnemy[i]->IsDetectDoor = false;
					}

					DoorPtr->DoorMainRenderer->ChangeAnimation("DoorOpen");
					DoorPtr->DoorGlowRenderer->Off();
					DoorPtr->DoorMainCollision->Off();

					PlayerPtr->FSM_PlayerState.ChangeState(FSM_PlayerState::DoorKick);
					return;
				}
			}
		}


	};

	DoorMainCollision->CollisionEvent(ContentsCollisionType::PlayerBody, DoorAutoOpenEvent);

}

void Door::DoorAttackOpenEvent()
{
	EventParameter DoorAttackOpenEvent;

	DoorAttackOpenEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Door* DoorPtr = dynamic_cast<Door*>(thisActor);


		for (size_t i = 0; i < DoorPtr->DetectedEnemy.size(); i++)
		{
			DoorPtr->DetectedEnemy[i]->IsDetectDoor = false;
		}


		DoorPtr->DoorMainRenderer->ChangeAnimation("DoorOpen");
		DoorPtr->DoorMainCollision->Off();
		DoorPtr->DoorGlowRenderer->Off();

	};


	DoorMainCollision->CollisionEvent(ContentsCollisionType::PlayerAttack, DoorAttackOpenEvent);

}

// 문과 접촉하면 리스트에 Enemy를 추가하고, 문이 비활성화될 때 리스트 속 Enemy들의 상태를 변경해줌.
// ★ 리플레이나 역재생시 벡터 내부에 저장된 정보가 초기화 되어야 한다.
void Door::DoorDetectEnemyEvent()
{
	EventParameter DoorDetectEnemyEvent;

	DoorDetectEnemyEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Door* DoorPtr = dynamic_cast<Door*>(thisActor);

		GameEngineActor* EnemyActor = Col->GetActor();
		Enemy* EnemyPtr = dynamic_cast<Enemy*>(EnemyActor);

		DoorPtr->DetectedEnemy.push_back(EnemyPtr);

		for (size_t i = 0; i < DoorPtr->DetectedEnemy.size(); i++)
		{
			DoorPtr->DetectedEnemy[i]->IsDetectDoor = true;
		}

		//if (Col == nullptr || false == Col->GetUpdateValue())
		//{
		//	EnemyPtr->IsDetectDoor = false;
		//}

		//if (false == EnemyPtr->IsDetectDoor)
		//{
		//	EnemyPtr->IsDetectDoor = true;
		//}

	};

	DoorDetectEnemyEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		//GameEngineActor* EnemyActor = Col->GetActor();
		//Enemy* EnemyPtr = dynamic_cast<Enemy*>(EnemyActor);

		//if (Col == nullptr || false == Col->GetUpdateValue())
		//{
		//	EnemyPtr->IsDetectDoor = false;
		//}

		//if (false == EnemyPtr->IsDetectDoor)
		//{
		//	EnemyPtr->IsDetectDoor = true;
		//}

	};

	DoorMainCollision->CollisionEvent(ContentsCollisionType::EnemyDetect, DoorDetectEnemyEvent);

}