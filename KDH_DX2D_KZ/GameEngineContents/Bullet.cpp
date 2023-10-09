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
	// bullet은 Enemy와 Player 모두 사용해야 하기 때문에 Collision 생성은 나중에 하도록 한다.
	BulletCollision = CreateComponent<GameEngineCollision>(_Type);
	BulletCollision->Transform.SetLocalScale({ 50, 50, 1 });

	BulletDir = _BulletDir;
	DurationTime = _DurationTime;

	IsUsingAutoDeath = _IsUsingAutoDeath;

}

void Bullet::Start()
{

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
		if (BulletDir == float4::RIGHT)
		{
			BulletRenderer->RightFlip();
			Transform.AddLocalPosition(float4::RIGHT);
		}

		else if (BulletDir == float4::LEFT)
		{
			BulletRenderer->LeftFlip();
			Transform.AddLocalPosition(float4::LEFT);
		}

	}

//	 상대와의 피격이 없을 때 시간이 지남에 따라 소멸하도록 설정
	if (GetLiveTime() > DurationTime && true == IsUsingAutoDeath)
	{
		Death();
	}

	
}
