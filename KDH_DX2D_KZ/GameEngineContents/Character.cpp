#include "PreCompile.h"
#include "Character.h"
#include "GameStateManager.h"
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
		GravityVector += { float4::DOWN * GravityPower * _Delta };
	}

	else
	{
		GravityReset();
	}

	Transform.AddWorldPosition(GravityVector * _Delta);
}

// ��� ĳ���ʹ� �ش� Color ��ġ�� �������� ���� �Ǻ��մϴ�.
bool Character::GetGroundPixelCollision()
{
	GameEngineColor Color;

	// ����ġ ������ �ٲ��ֱ�
	if (CharType == CharacterType::NormalEnemy)
	{
		// ���� ��� Idle���� -50
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

void Character::Reverse()
{
	if (ActorInfo.size() == 0)
	{
		// ����� �����͸� ��� ����ϰ� ���� ���ӿ��� ó���� �����ϰ� �ٽ� �����մϴ�.
		GameStateManager::GameState->SetGameOverOff();
		return;
	}

	if (true == IsRecordPlayMode)
	{
		ReverseActorInfo& Info = ActorInfo.back();
		Transform.SetWorldPosition(Info.Pos);
		ActorInfo.pop_back();


		for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
		{
			std::shared_ptr<GameEngineSpriteRenderer> Renderer = Renderers[i];
			ReverseRendererInfo& Info = RendererInfo.back();
			Renderer->SetSprite(Info.SpriteName, Info.Frame);


			// ������ ���� ��ȯ
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
			MsgBoxAssert("����� �� ������ �߻��߽��ϴ�. �����Ͱ� �����ϴ�.");
		}
	}
}

void Character::Replay()
{
	if (ActorInfo.size() == 0)
	{
	//	GameStateManager::GameState->SetGameClearOff();
		// ����� �����͸� ��� ����ϰ� ���� �����մϴ�.
		// ���̵���/�ƿ� �� �� ȭ�� ��ȯ �ʿ�
		return;
	}

	ReverseActorInfo& Info = ActorInfo.front();
	Transform.SetWorldPosition(Info.Pos);
	ActorInfo.pop_front();

	for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = Renderers[i];
		ReverseRendererInfo& Info = RendererInfo.front();
		Renderer->SetSprite(Info.SpriteName, Info.Frame);


		// ������ ���� ��ȯ
		int FilpDir = Info.FilpDir;

		if (FilpDir == 0)
		{
			Renderer->RightFlip();
		}

		else if (FilpDir == 1)
		{
			Renderer->LeftFlip();
		}

		RendererInfo.pop_front();
	}

	if (true == ActorInfo.empty() && false == RendererInfo.empty())
	{
		MsgBoxAssert("����� �� ������ �߻��߽��ϴ�. �����Ͱ� �����ϴ�.");
	}


	//LastAniInfos.clear();

	//for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
	//{
	//	std::shared_ptr<GameEngineFrameAnimation> CurAni = Renderers[i]->CurAnimation();

	//	LastAniInfo Info;

	//	Info.AniName = CurAni->AnimationName;
	//	Info.Index = CurAni->CurIndex;

	//	LastAniInfos.push_back(Info);
	//}

	//for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
	//{
	//	Renderers[i]->ChangeAnimation(LastAniInfos[i].AniName, LastAniInfos[i].Index);
	//}
}

// Reverse
// Update
// UpdateAddingReverseData

// ���� ������Ʈ�� �ϸ�
// ���� �����̰� �̵��ϰ� �ɰž�.

void Character::UpdateAddingReverseData(float _Delta)
{
	if (false == IsRecordPlayMode)
	{
		ActorInfo.push_back({ 0.0f, Transform.GetWorldPosition() });

		for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
		{
			// Push�� ������ �غ�
			float4 SpriteScale = Renderers[i]->Transform.GetLocalScale();
			std::string_view SpriteName = Renderers[i]->GetSprite()->GetName();
			std::string Name = GameEngineString::ToUpperReturn(SpriteName);
			int Frame = Renderers[i]->GetCurIndex();
			int FilpDir = Renderers[i]->GetSpriteRendererInfoValue().FlipLeft;

			RendererInfo.push_back({ 0.0f, i, SpriteName, Frame, FilpDir });
		}
	}
}

void Character::RecordPlayModeOff()
{
	if (false == IsRecordPlayMode)
	{
		return;
	}

	IsRecordPlayMode = false;

	for (int i = 0; i < static_cast<int>(Renderers.size()); i++)
	{
		Renderers[i]->ChangeAnimation(LastAniInfos[i].AniName, LastAniInfos[i].Index);
	}
}

void Character::RecordPlayModeOn()
{
	if (true == IsRecordPlayMode)
	{
		return;
	}

	IsRecordPlayMode = true;

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