#include "PreCompile.h"
#include "Pawn.h"
#include "GameStateManager.h"

Pawn::Pawn()
{
}

Pawn::~Pawn()
{
}

void Pawn::SetMapTexture(std::string_view _MapTextureName)
{
	MapTexture = GameEngineTexture::Find(_MapTextureName);

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("ERROR : �������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�. �Է��� �ؽ�ó �̸��� �ٽ� Ȯ���ϼ���.");
	}
}

GameEngineColor Pawn::GetMapColor(float4 _Pos, GameEngineColor _DefaultColor)
{

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("ERROR : �� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�. ���� �������� �ؽ�ó�� �������ּ���.");
	}

	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
	_Pos.Y *= -1.0f;

	return MapTexture->GetColor(_Pos, _DefaultColor);
}


// Reverse
// Update
// UpdateAddingRecordData

// ���� ������Ʈ�� �ϸ�
// ���� �����̰� �̵��ϰ� �ɰž�.

void Pawn::RecordPlayModeOn()
{
	if (true == IsRecordPlayMode)
	{
		return;
	}

	IsRecordPlayMode = true;

	LastAniInfos.clear();

	for (int i = 0; i < static_cast<int>(RecordingRenderers.size()); i++)
	{
		std::shared_ptr<GameEngineFrameAnimation> CurAni = RecordingRenderers[i]->CurAnimation();

		LastAniInfo Info;

		Info.AniName = CurAni->AnimationName;
		Info.Index = CurAni->CurIndex;

		LastAniInfos.push_back(Info);
	}

}

void Pawn::RecordPlayModeOff()
{
	if (false == IsRecordPlayMode)
	{
		return;
	}

	IsRecordPlayMode = false;

	for (int i = 0; i < static_cast<int>(RecordingRenderers.size()); i++)
	{
		RecordingRenderers[i]->ChangeAnimation(LastAniInfos[i].AniName, LastAniInfos[i].Index);
	}
}

void Pawn::Reverse(float _Delta)
{

	static float Timer = 0.0f;

	Timer += _Delta;

	if (ActorInfo.size() == 0)
	{
		// ����� �����͸� ��� ����ϰ� ���� ���ӿ��� ó���� �����ϰ� �ٽ� �����մϴ�.
		GameStateManager::GameState->SetGameOverOff();
		return;
	}

	if (true == IsRecordPlayMode && Timer > 1.0f)
	{
		int tt = static_cast<int>((Timer / TimeLimit + 1.0f));

		for (int i = 0; i < tt; i++)
		{
			if (!ActorInfo.empty())
			{
				ReverseActorInfo& Info = ActorInfo.back();
				Transform.SetWorldPosition(Info.Pos);
				ActorInfo.pop_back();
			}

			if (!RendererInfo.empty())
			{
				for (int i = 0; i < static_cast<int>(RecordingRenderers.size()); i++)
				{
					std::shared_ptr<GameEngineSpriteRenderer> Renderer = RecordingRenderers[i];
					ReverseRendererInfo& Info = RendererInfo.back();
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

					RendererInfo.pop_back();
				}

			}

			if (true == ActorInfo.empty() && false == RendererInfo.empty())
			{
				MsgBoxAssert("����� �� ������ �߻��߽��ϴ�. �����Ͱ� �����ϴ�.");
			}
		}
	}
	//else
	//{
	//	if (!ActorInfo.empty())
	//	{
	//		ReverseActorInfo& Info = ActorInfo.back();
	//		Transform.SetWorldPosition(Info.Pos);
	//		ActorInfo.pop_back();
	//	}

	//	if (!RendererInfo.empty())
	//	{
	//		for (int i = 0; i < static_cast<int>(RecordingRenderers.size()); i++)
	//		{
	//			std::shared_ptr<GameEngineSpriteRenderer> Renderer = RecordingRenderers[i];
	//			ReverseRendererInfo& Info = RendererInfo.back();
	//			Renderer->SetSprite(Info.SpriteName, Info.Frame);


	//			// ������ ���� ��ȯ
	//			int FilpDir = Info.FilpDir;

	//			if (FilpDir == 0)
	//			{
	//				Renderer->RightFlip();
	//			}

	//			else if (FilpDir == 1)
	//			{
	//				Renderer->LeftFlip();
	//			}

	//			RendererInfo.pop_back();
	//		}
	//	}
	//}
}

void Pawn::Replay()
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

	for (int i = 0; i < static_cast<int>(RecordingRenderers.size()); i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = RecordingRenderers[i];
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
}

void Pawn::UpdateAddingRecordData(float _Delta)
{
	if (false == IsRecordPlayMode)
	{
		ActorInfo.push_back({ 0.0f, Transform.GetWorldPosition() });

		for (int i = 0; i < static_cast<int>(RecordingRenderers.size()); i++)
		{
			// Push�� ������ �غ�
			float4 SpriteScale = RecordingRenderers[i]->Transform.GetLocalScale();
			std::string_view SpriteName = RecordingRenderers[i]->GetSprite()->GetName();
			std::string Name = GameEngineString::ToUpperReturn(SpriteName);
			int Frame = RecordingRenderers[i]->GetCurIndex();
			int FilpDir = RecordingRenderers[i]->GetSpriteRendererInfoValue().FlipLeft;

			RendererInfo.push_back({ 0.0f, i, SpriteName, Frame, FilpDir });
		}
	}
}

void Pawn::OnDamaged(int _iAttackPower)
{
}
