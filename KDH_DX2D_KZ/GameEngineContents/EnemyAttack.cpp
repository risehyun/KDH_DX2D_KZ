#include "PreCompile.h"
#include "EnemyAttack.h"

// �� ���� ������ �ϳ��� Ŭ������ ��� ó�� (�÷��̾�, ���ʹ� ��ΰ� ��� ����)
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