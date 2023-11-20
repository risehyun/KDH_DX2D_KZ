#include "PreCompile.h"
#include "Character.h"
#include "GameStateManager.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Gravity(float _Delta)
{
	// 중력을 사용하지 않는 경우 리턴하여 아래의 함수가 실행되지 않도록 합니다.
	if (false == IsGravity)
	{
		return;
	}

	// 허공에 있는 경우
	if (true == GetGroundPixelCollision())
	{
		GravityVector += { float4::DOWN * GravityPower * _Delta };
	}

	else
	{
		GravityReset();
	}

	Transform.AddWorldPosition(GravityVector * _Delta);
}

// 모든 캐릭터는 해당 Color 위치를 기준으로 땅을 판별합니다.
bool Character::GetGroundPixelCollision()
{
	GameEngineColor Color;

	// 스위치 문으로 바꿔주기
	if (CharType == CharacterType::NormalEnemy)
	{
		// 적의 경우 Idle에서 -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 40.0f }, GameEngineColor::RED);
	}

	else if (CharType == CharacterType::Player || CharType == CharacterType::Boss)
	{
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 40.0f }, GameEngineColor::RED);
	}

	else if (CharType == CharacterType::BossHead)
	{
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 10.0f }, GameEngineColor::RED);
	}

	else
	{
		// 적의 경우 Idle에서 -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 32.0f }, GameEngineColor::RED);
	}

	if (GameEngineColor::WHITE == Color)
	{
		return true;
	}

	// 허공이 아닌 경우 (땅에 있는 경우)
	else
	{
		return false;
	}

}

float4 Character::ActorCameraPos()
{
	return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
}

void Character::Reverse()
{
	if (ActorInfo.size() == 0)
	{
		GameStateManager::GameState->SetGameOverOff();
		return;
	}

	if (true == IsReverse)
	{
		ReverseActorInfo& Info = ActorInfo.back();
		Transform.SetWorldPosition(Info.Pos);
		ActorInfo.pop_back();


		for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
		{
			std::shared_ptr<GameEngineSpriteRenderer> Renderer = Renderers[i];
			ReverseRendererInfo& Info = RendererInfo.back();
			Renderer->SetSprite(Info.SpriteName, Info.Frame);


			// 렌더러 방향 전환
			int FilpDir = Info.FilpDir;

			if (FilpDir == 0)
			{
				Renderer->RightFlip();
			}

			else if(FilpDir == 1)
			{
				Renderer->LeftFlip();
			}
			RendererInfo.pop_back();
		}

		if (true == ActorInfo.empty() && false == RendererInfo.empty())
		{
			MsgBoxAssert("역재생 중 오류가 발생했습니다. 데이터가 없습니다.");
		}
	}
}

// Reverse
// Update
// UpdateAddingReverseData

// 내가 업데이트를 하면
// 나는 움직이고 이동하게 될거야.

void Character::UpdateAddingReverseData(float _Delta)
{
	if (false == IsReverse)
	{
		ActorInfo.push_back({ 0.0f, Transform.GetWorldPosition() });

		for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
		{
			// Push할 데이터 준비
			float4 SpriteScale = Renderers[i]->Transform.GetLocalScale();
			std::string_view SpriteName = Renderers[i]->GetSprite()->GetName();
			std::string Name = GameEngineString::ToUpperReturn(SpriteName);
			int Frame = Renderers[i]->GetCurIndex();
			int FilpDir = Renderers[i]->GetSpriteRendererInfoValue().FlipLeft;

			RendererInfo.push_back({ 0.0f, i, SpriteName, Frame, FilpDir });
		}
	}
}

void Character::ReverseOff()
{
	if (false == IsReverse)
	{
		return;
	}

	IsReverse = false;

	for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
	{
		Renderers[i]->ChangeAnimation(LastAniInfos[i].AniName, LastAniInfos[i].Index);
	}
}

void Character::ReverseOn()
{
	if (true == IsReverse)
	{
		return;
	}

	IsReverse = true;

	LastAniInfos.clear();

	for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
	{
		std::shared_ptr<GameEngineFrameAnimation> CurAni = Renderers[i]->CurAnimation();

		LastAniInfo Info;

		Info.AniName = CurAni->AnimationName;
		Info.Index = CurAni->CurIndex;

		LastAniInfos.push_back(Info);
	}

}