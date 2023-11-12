#include "PreCompile.h"
#include "BossHead.h"

BossHead::BossHead()
{
}

BossHead::~BossHead()
{
}

void BossHead::Start()
{
	BossHeadRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	BossHeadRenderer->AutoSpriteSizeOn();
	BossHeadRenderer->CreateAnimation("Head_Hurtfly", "spr_headhunter_head_hurtfly", 0.1f, 0, 7, false);
	BossHeadRenderer->CreateAnimation("Head_HurtGround", "spr_headhunter_head_hurtground", 0.1f, 0, 7, false);
	BossHeadRenderer->ChangeAnimation("Head_Hurtfly");
}

void BossHead::Update(float _Delta)
{
	static const float4 gravity = { 0.0f, -9.8f };
	static const float coef_res = 0.5f;

	if (GetLiveTime() < 2.0f)
	{
		Velocity += gravity;

		Transform.AddLocalPosition(MovePos * 600.0f * _Delta);
		Transform.AddLocalPosition(Velocity * _Delta * Speed);
	
		// 아래
		if (-430.0f > Transform.GetLocalPosition().Y)
		{
			MovePos = float4::ZERO;
			Velocity = 0.0f;

			if (true == BossHeadRenderer->IsCurAnimation("Head_Hurtfly")
				&& true == BossHeadRenderer->IsCurAnimationEnd())
			{
				BossHeadRenderer->ChangeAnimation("Head_HurtGround");
			}
		}

		// 오른쪽
		if (1128.0f < Transform.GetLocalPosition().X)
		{
			MovePos = { (float4::LEFT + float4::DOWN) * coef_res };
		}

		// 왼쪽
		else if (160.0f > Transform.GetLocalPosition().X)
		{
			MovePos = { (float4::RIGHT + float4::DOWN) * coef_res };
		}


	}

}
