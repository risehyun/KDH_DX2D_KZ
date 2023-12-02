#include "PreCompile.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "Bullet.h"
#include "BossGrenade.h"
#include "Fx.h"

PlayerAttack::PlayerAttack()
{
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Start()
{
	PlayerAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerAttack);
	PlayerAttackCollision->Transform.SetLocalScale({ 100, 100 });

	{
		PlayerAttackRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		PlayerAttackRenderer->CreateAnimation("AttackSlash", "spr_dragon_slash", 0.1f, 0, 4, false);
		PlayerAttackRenderer->AutoSpriteSizeOn();
		PlayerAttackRenderer->ChangeAnimation("AttackSlash");
	}
}

void PlayerAttack::Update(float _Delta)
{
	if (PlayerAttackCollision != nullptr)
	{
		BossParryEvent();

		EventParameter ParryingCollisionEvent;

		ParryingCollisionEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* EnemyAttackActor = Col->GetActor();
			Bullet* EnemyBulletPtr = dynamic_cast<Bullet*>(EnemyAttackActor);

			if (true == Player::MainPlayer->GetParryable() && EnemyBulletPtr != nullptr)
			{
				std::shared_ptr<Bullet> PlayerParryBullet = Player::MainPlayer->GetLevel()->CreateActor<Bullet>(static_cast<int>(ContentsRenderType::Play));

				Player::MainPlayer->FxPlayer = GameEngineSound::SoundPlay("sound_bulletparry_slash.wav");

				std::shared_ptr<Fx> NewReflectFx = Player::MainPlayer->GetLevel()->CreateActor<Fx>();
				NewReflectFx->SetFxData(EFx_Type::BulletReflect, float4::ZERO);
				NewReflectFx->Transform.SetLocalPosition(EnemyBulletPtr->Transform.GetWorldPosition());

				std::shared_ptr<Fx> NewSlashFx = Player::MainPlayer->GetLevel()->CreateActor<Fx>();
				NewSlashFx->SetFxData(EFx_Type::Slash, float4::ZERO);
				NewSlashFx->Transform.SetLocalPosition(EnemyBulletPtr->Transform.GetWorldPosition());

				float4 PlayerBulletDir = -EnemyBulletPtr->GetBulletDir();

				float4 EnemyBulletPos = EnemyBulletPtr->InitPos;
				float4 PlayerBulletPos = EnemyBulletPtr->Transform.GetWorldPosition();

				PlayerParryBullet->InitBulletData(ContentsCollisionType::PlayerAttack, PlayerBulletDir, 0.5f);

				if (EnemyBulletPtr->GetName() == "Turret")
				{
					float4 angle = atan2(EnemyBulletPos.Y - PlayerBulletPos.Y,
						EnemyBulletPos.X - PlayerBulletPos.X);

					PlayerParryBullet->Transform.SetLocalRotation({ 0.0f, 0.0f, angle.X * GameEngineMath::R2D });
				}

				if (EnemyBulletPtr != nullptr)
				{
					PlayerParryBullet->Transform.SetLocalPosition(EnemyBulletPtr->Transform.GetWorldPosition());

			
					EnemyBulletPtr->Death();
				}

				Player::MainPlayer->OffParryable();
			}

		};

		PlayerAttackCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, ParryingCollisionEvent);

	}

	if (true == PlayerAttackRenderer->IsCurAnimationEnd())
	{
		Death();
	}

}

void PlayerAttack::BossParryEvent()
{
	EventParameter ParryingCollisionEvent;

	ParryingCollisionEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

		GameEngineActor* EnemyAttackActor = Col->GetActor();
		BossGrenade* EnemyBulletPtr = dynamic_cast<BossGrenade*>(EnemyAttackActor);

		if (true == Player::MainPlayer->GetParryable())
		{
			std::shared_ptr<BossGrenade> PlayerParryBullet = Player::MainPlayer->GetLevel()->CreateActor<BossGrenade>(static_cast<int>(ContentsRenderType::Play));
			PlayerParryBullet->SetSelfAttackable();
			PlayerDir PlayerCurrentDir = Player::MainPlayer->GetPlayerDirEnum();
			if (PlayerCurrentDir == PlayerDir::Right
				|| PlayerCurrentDir == PlayerDir::RightDown
				|| PlayerCurrentDir == PlayerDir::RightUp)
			{
				PlayerParryBullet->SetGrenadeDir(float4::RIGHT);
			}
			else
			{
				PlayerParryBullet->SetGrenadeDir(float4::LEFT);
			}


			PlayerParryBullet->Transform.SetLocalPosition({ EnemyBulletPtr->Transform.GetWorldPosition().X, EnemyBulletPtr->Transform.GetWorldPosition().Y });

			std::shared_ptr<Fx> NewSlashFx = Player::MainPlayer->GetLevel()->CreateActor<Fx>();
			NewSlashFx->SetFxData(EFx_Type::Slash, float4::ZERO);
			NewSlashFx->Transform.SetLocalPosition(EnemyBulletPtr->Transform.GetWorldPosition());


			if (EnemyBulletPtr != nullptr)
			{
				EnemyBulletPtr->Death();
			}

			Player::MainPlayer->OffParryable();
		}

	};

	PlayerAttackCollision->CollisionEvent(ContentsCollisionType::BossGrenade, ParryingCollisionEvent);

}
