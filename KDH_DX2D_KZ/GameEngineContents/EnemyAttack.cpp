#include "PreCompile.h"
#include "EnemyAttack.h"

// ★ 근접 공격은 하나의 클래스로 묶어서 처리 (플레이어, 에너미 모두가 사용 가능)
/*
	PlayerAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::PlayerAttack);
	PlayerAttackCollision->Transform.SetLocalScale({ 40, 50, 1 });

	{
		PlayerAttackRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		PlayerAttackRenderer->CreateAnimation("AttackSlash", "spr_dragon_slash", 0.1f, 0, 4, false);
		PlayerAttackRenderer->AutoSpriteSizeOn();
		PlayerAttackRenderer->ChangeAnimation("AttackSlash");
	}


*/