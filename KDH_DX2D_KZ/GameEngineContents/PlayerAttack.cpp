#include "PreCompile.h"
#include "PlayerAttack.h"

PlayerAttack::PlayerAttack()
{
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Start()
{

	PlayerAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerAttack);
	PlayerAttackCollision->Transform.SetLocalScale({ 30, 30, 1 });

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
	if (true == PlayerAttackRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}