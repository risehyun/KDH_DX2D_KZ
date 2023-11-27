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

	// bullet은 Enemy와 Player 모두 사용해야 하기 때문에 Collision 생성은 나중에 하도록 한다.
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

	//	 상대와의 피격이 없을 때 시간이 지남에 따라 소멸하도록 설정
	if (GetLiveTime() > DurationTime && true == IsUsingAutoDeath)
	{
		Death();
	}
}
