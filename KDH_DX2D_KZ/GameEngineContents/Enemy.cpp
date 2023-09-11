#include "PreCompile.h"
#include "Enemy.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::ChangeState(EnemyState State)
{
}

void Enemy::StateUpdate(float _Delta)
{
}

void Enemy::DirCheck()
{
}

void Enemy::ChangeAnimationState(std::string_view _StateName)
{
}

void Enemy::IdleStart()
{
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
}

void Enemy::AttackUpdate(float _Delta)
{
}

void Enemy::DeathStart()
{
}

void Enemy::DeathUpdate(float _Delta)
{
}

void Enemy::Start()
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("GameEngineResources");
	//	Dir.MoveChild("ContentsResources");
	//	Dir.MoveChild("FolderTexture");
	//	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	//	for (size_t i = 0; i < Directorys.size(); i++)
	//	{
	//		GameEngineDirectory& Dir = Directorys[i];

	//		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//	}
	//}

	{
		EnemyMainRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

		EnemyMainRenderer->CreateAnimation("Idle", "spr_gangsteridle");

		EnemyMainRenderer->AutoSpriteSizeOn();
	}

	EnemyMainRenderer->ChangeAnimation("Idle");

	TestCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	TestCollision->Transform.SetLocalScale({ 30, 30, 1 });
}

void Enemy::Update(float _Delta)
{
}
