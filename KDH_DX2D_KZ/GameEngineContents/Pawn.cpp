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
		MsgBoxAssert("ERROR : 존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다. 입력한 텍스처 이름을 다시 확인하세요.");
	}
}

GameEngineColor Pawn::GetMapColor(float4 _Pos, GameEngineColor _DefaultColor)
{

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("ERROR : 땅 체크용 텍스처가 존재하지 않습니다. 먼저 레벨에서 텍스처를 지정해주세요.");
	}

	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	return MapTexture->GetColor(_Pos, _DefaultColor);
}


// Reverse
// Update
// UpdateAddingRecordData

// 내가 업데이트를 하면
// 나는 움직이고 이동하게 될거야.

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
		// 저장된 데이터를 모두 재생하고 나면 게임오버 처리를 해제하고 다시 시작합니다.
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


					// 렌더러 방향 전환
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
				MsgBoxAssert("역재생 중 오류가 발생했습니다. 데이터가 없습니다.");
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


	//			// 렌더러 방향 전환
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
			// 저장된 데이터를 모두 재생하고 나면 리턴합니다.
			// 페이드인/아웃 한 뒤 화면 전환 필요
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


		// 렌더러 방향 전환
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
		MsgBoxAssert("역재생 중 오류가 발생했습니다. 데이터가 없습니다.");
	}
}

void Pawn::UpdateAddingRecordData(float _Delta)
{
	if (false == IsRecordPlayMode)
	{
		ActorInfo.push_back({ 0.0f, Transform.GetWorldPosition() });

		for (int i = 0; i < static_cast<int>(RecordingRenderers.size()); i++)
		{
			// Push할 데이터 준비
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
