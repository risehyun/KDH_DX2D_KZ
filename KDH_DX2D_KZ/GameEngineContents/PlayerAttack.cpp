#include "PreCompile.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "Bullet.h"

PlayerAttack::PlayerAttack()
{
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Start()
{

	PlayerAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerAttack);
	PlayerAttackCollision->Transform.SetLocalScale({ 40, 50, 1 });

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
		PlayerAttackRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		PlayerAttackRenderer->CreateAnimation("AttackSlash", "spr_dragon_slash", 0.1f, 0, 4, false);

		//		MainSpriteRenderer->AutoSpriteSizeOn();

		PlayerAttackRenderer->AutoSpriteSizeOn();

		PlayerAttackRenderer->ChangeAnimation("AttackSlash");
	}
}

void PlayerAttack::Update(float _Delta)
{

	EventParameter ParryingCollisionEvent;

	ParryingCollisionEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{

		GameEngineActor* EnemyAttackActor = Col->GetActor();
		Bullet* EnemyBulletPtr = dynamic_cast<Bullet*>(EnemyAttackActor);

		if (true == Player::MainPlayer->GetParryable())
		{
			std::shared_ptr<Bullet> PlayerParryBullet = Player::MainPlayer->GetLevel()->CreateActor<Bullet>(static_cast<int>(ContentsRenderType::Play));
			PlayerDir PlayerCurrentDir = Player::MainPlayer->GetPlayerDirEnum();
			if (PlayerCurrentDir == PlayerDir::Right
				|| PlayerCurrentDir == PlayerDir::RightDown
				|| PlayerCurrentDir == PlayerDir::RightUp)
			{
				PlayerParryBullet->InitBulletData(ContentsCollisionType::PlayerAttack, float4::RIGHT, 3.0f);
			}
			else
			{
				PlayerParryBullet->InitBulletData(ContentsCollisionType::PlayerAttack, float4::LEFT, 3.0f);
			}

			PlayerParryBullet->Transform.SetLocalPosition({ EnemyBulletPtr->Transform.GetWorldPosition().X, EnemyBulletPtr->Transform.GetWorldPosition().Y });

			EnemyBulletPtr->Death();

			 
			Player::MainPlayer->OffParryable();
		}

	};

	PlayerAttackCollision->CollisionEvent(ContentsCollisionType::EnemyAttack, ParryingCollisionEvent);








	if (true == PlayerAttackRenderer->IsCurAnimationEnd())
	{
		Death();
	}

}