#include "PreCompile.h"
#include "Character.h"

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
		GravityVector += float4::DOWN * GravityPower * _Delta;
	}

	else
	{
		GravityReset();
	}

	Transform.AddLocalPosition(GravityVector * _Delta);
}

bool Character::GetGroundPixelCollision()
{
	GameEngineColor Color;

	if (CharType == CharacterType::NormalEnemy)
	{
		// 적의 경우 Idle에서 -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 50.0f }, GameEngineColor::RED);
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
	if (true == IsReverse)
	{
		if (ActorInfo.size() == 0)
		{
			ActorInfo.clear();
			IsReverse = false;
		}


		//int temp = RendererInfo.size() / Renderers.size();

		//if (ActorInfo.size() != RendererInfo.size() / Renderers.size())
		//{
		//	MsgBoxAssert("ActorInfo.size() != RendererInfo.size() / Renderers.size()");
		//}

		else
		{
			ReverseActorInfo& Info = ActorInfo.back();

			Transform.SetWorldPosition(Info.Pos);
			ActorInfo.pop_back();

		}


		//for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
		//{
		//	std::shared_ptr<GameEngineSpriteRenderer> Renderer = Renderers[i];
		//	ReverseRendererInfo& Info = RendererInfo.back();
		//	Renderer->SetSprite(Info.SpriteName, Info.Frame);
		//}
	}
}

void Character::ReverseUpdate(float _Delta)
{
	if (false == IsReverse)
	{
		ActorInfo.push_back({ 0.0f, Transform.GetWorldPosition() });

		//for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
		//{
		//	std::string_view SpriteName = Renderers[i]->GetSprite()->GetName();
		//	int Frame = Renderers[i]->GetCurIndex();
		//	RendererInfo.push_back({ 0.0f, i, SpriteName, Frame });
		//}
	}

	else
	{
		Reverse();
	}
}
