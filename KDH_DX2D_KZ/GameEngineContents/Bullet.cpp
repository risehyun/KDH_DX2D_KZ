#include "PreCompile.h"
#include "Bullet.h"
#include "Player.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::InitBulletData(ContentsCollisionType _Type, float4 _BulletDir, float _DurationTime, bool _IsUsingAutoDeath)
{
	// bullet�� Enemy�� Player ��� ����ؾ� �ϱ� ������ Collision ������ ���߿� �ϵ��� �Ѵ�.

	Type = _Type;

	BulletCollision = CreateComponent<GameEngineCollision>(Type);
	BulletCollision->Transform.SetLocalScale({ 50, 50, 1 });

	BulletDir = _BulletDir;
	DurationTime = _DurationTime;

	IsUsingAutoDeath = _IsUsingAutoDeath;

}

void Bullet::Start()
{

	InitPos = Transform.GetLocalPosition();

	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));

	BulletRenderer->CreateAnimation("FireBullet", "spr_bullet", 0.1f, 0, 4, false);
	BulletRenderer->AutoSpriteSizeOn();

	BulletRenderer->ChangeAnimation("FireBullet");
}

void Bullet::Update(float _Delta)
{

	if (true == Player::MainPlayer->IsDeath)
	{
		Death();
	}

	if (BulletDir == float4::LEFT)
	{
		BulletRenderer->LeftFlip();
	}
	else
	{
		BulletRenderer->RightFlip();
	}

	if (GetLiveTime() < DurationTime)
	{

		Speed = 5.0f;
		
		Transform.AddLocalPosition(BulletDir * _Delta * Speed);

	}

//	 ������ �ǰ��� ���� �� �ð��� ������ ���� �Ҹ��ϵ��� ����
	if (GetLiveTime() > DurationTime && true == IsUsingAutoDeath)
	{
		Death();
	}

	
}
