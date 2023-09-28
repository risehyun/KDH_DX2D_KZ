#include "PreCompile.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::InitBulletData(ContentsCollisionType _Type, float4 _BulletDir)
{
	// bullet�� Enemy�� Player ��� ����ؾ� �ϱ� ������ Collision ������ ���߿� �ϵ��� �Ѵ�.
	BulletCollision = CreateComponent<GameEngineCollision>(_Type);
	BulletCollision->Transform.SetLocalScale({ 30, 30, 1 });

	BulletDir = _BulletDir;
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

	if (GetLiveTime() < 3.0f)
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

	// ������ �ǰ��� ���� �� �ð��� ������ ���� �Ҹ��ϵ��� ����
	//if (GetLiveTime() > 2.5f)
	//{
	//	Death();
	//}


}
