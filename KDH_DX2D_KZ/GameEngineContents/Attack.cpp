#include "PreCompile.h"
#include "Attack.h"
#include "Player.h"

Attack::Attack()
{
}

Attack::~Attack()
{
}

void Attack::InitAttackData(ContentsCollisionType _Type, float4 _AttackDir, float _DurationTime, bool _IsUsingAutoDeath)
{
	AttackDir = _AttackDir;
	DurationTime = _DurationTime;

	IsUsingAutoDeath = _IsUsingAutoDeath;

	// bullet�� Enemy�� Player ��� ����ؾ� �ϱ� ������ Collision ������ ���߿� �ϵ��� �Ѵ�.
	AttackCollision = CreateComponent<GameEngineCollision>(_Type);
	AttackCollision->Transform.SetLocalScale({ 80, 80, 1 });
	AttackCollision->Transform.SetLocalPosition({ _AttackDir.X * 10.0f });



}

void Attack::Start()
{
}

void Attack::Update(float _Delta)
{
	if (true == Player::MainPlayer->IsDeath)
	{
		Death();
	}

	//	 ������ �ǰ��� ���� �� �ð��� ������ ���� �Ҹ��ϵ��� ����
	if (GetLiveTime() > DurationTime && true == IsUsingAutoDeath)
	{
		Death();
	}
}
