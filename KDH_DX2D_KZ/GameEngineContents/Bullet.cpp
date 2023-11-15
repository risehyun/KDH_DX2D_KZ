#include "PreCompile.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::InitBulletData(ContentsCollisionType _Type, float4 _BulletDir, float _DurationTime, bool _IsUsingAutoDeath)
{
	// bullet�� Enemy�� Player ��� ����ؾ� �ϱ� ������ Collision ������ ���߿� �ϵ��� �Ѵ�.
	BulletCollision = CreateComponent<GameEngineCollision>(_Type);
	BulletCollision->Transform.SetLocalScale({ 50, 50, 1 });

	BulletDir = _BulletDir;
	DurationTime = _DurationTime;

	IsUsingAutoDeath = _IsUsingAutoDeath;

}

void Bullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

	BulletRenderer->Transform.SetLocalPosition({ 0.f, 0.f, 0.f, 1.f });

	BulletRenderer->CreateAnimation("FireBullet", "spr_bullet", 0.1f, 0, 4, false);
	BulletRenderer->AutoSpriteSizeOn();

	BulletRenderer->ChangeAnimation("FireBullet");
}

void Bullet::Update(float _Delta)
{
	if (GetLiveTime() < DurationTime)
	{
		Transform.AddLocalPosition(BulletDir * _Delta);
	}

//	 ������ �ǰ��� ���� �� �ð��� ������ ���� �Ҹ��ϵ��� ����
	if (GetLiveTime() > DurationTime && true == IsUsingAutoDeath)
	{
		Death();
	}

	
}
