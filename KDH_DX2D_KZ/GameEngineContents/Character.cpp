#include "PreCompile.h"
#include "Character.h"
#include "Player.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Gravity(float _Delta)
{
	// �߷��� ������� �ʴ� ��� �����Ͽ� �Ʒ��� �Լ��� ������� �ʵ��� �մϴ�.
	if (false == IsGravity)
	{
		return;
	}

	// ����� �ִ� ���
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
		// ���� ��� Idle���� -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 50.0f }, GameEngineColor::RED);
	}
	else
	{
		// ���� ��� Idle���� -50
		Color = GetMapColor({ Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y - 32.0f }, GameEngineColor::RED);
	}

	if (GameEngineColor::WHITE == Color)
	{
		return true;
	}

	// ����� �ƴ� ��� (���� �ִ� ���)
	else
	{
		return false;
	}

}

float4 Character::ActorCameraPos()
{
	return Transform.GetWorldPosition() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
}
//
//void Character::Reverse()
//{
//	if (true == IsReverse)
//	{
//		if (ActorInfo.size() == 0)
//		{
//			ActorInfo.clear();
//			IsReverse = false;
//		}
//
//		//	int temp = RendererInfo.size() / Renderers.size();
//
//		//if (ActorInfo.size() != RendererInfo.size() / Renderers.size())
//		//{
//		//	MsgBoxAssert("ActorInfo.size() != RendererInfo.size() / Renderers.size()");
//		//}
//
//		else
//		{
//			ReverseActorInfo& Info = ActorInfo.back();
//			Transform.SetWorldPosition(Info.Pos);
//
//			//if (nullptr != Info.SpriteName)
//			//{
//				Player::MainPlayer->ReverseSpriteRenderer->SetSprite(Info.SpriteName, Info.Frame);
//				int a = 0;
////			}
//
//
//			ActorInfo.pop_back();
//
//			//for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
//			//{
//			//	std::shared_ptr<GameEngineSpriteRenderer> Renderer = Player::MainPlayer->GetMainRenderer();
//			//	ReverseRendererInfo& RenderInfo = RendererInfo.back();
//
//			//	//int TestFrame = RenderInfo.Frame;
//			//	//std::string_view TestString = RenderInfo.SpriteName;
//			//	//int a = 0;
//
//			//	Renderer->SetSprite(RenderInfo.SpriteName, RenderInfo.Frame);
//			//}
//		}
//	}
//}
//
//void Character::ReverseUpdate(float _Delta)
//{
//	if (false == IsReverse)
//	{
//		ActorInfo.push_back({ 0.0f, Transform.GetWorldPosition() });
//
//		//for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
//		//{
//		//	std::string_view SpriteName = Player::MainPlayer->GetMainRenderer()->GetSprite()->GetName();
//		//	RendererInfo.push_back({ 0.0f, i, SpriteName, Frame });
//		//	int a = 0;
//		//}
//	}
//
//	else
//	{
//		Reverse();
//	}
//}
