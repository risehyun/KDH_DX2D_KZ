#include "PreCompile.h"
#include "Portal.h"

Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::Start()
{

	GameEngineInput::AddInputObject(this);

	//	1. 콜리전 만들기

	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->Transform.SetLocalScale({ 100, 100, 1 });

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


	{
		InputRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
		InputRenderer->CreateAnimation("Space", "spr_spacebar", 0.5f, 0, 1, true);
		InputRenderer->AutoSpriteSizeOn();
		InputRenderer->Transform.SetLocalPosition({Transform.GetWorldPosition().X, Transform.GetWorldPosition().Y + 100.f});
		InputRenderer->ChangeAnimation("Space");
		InputRenderer->Off();
	}
}

void Portal::Update(float _Delta)
{
	//  2. 플레이어와 충돌 이벤트 설정하기 

	EventParameter InteractEvent;

	InteractEvent.Enter = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* thisActor = _this->GetActor();
			Portal* PortalPtr = dynamic_cast<Portal*>(thisActor);

			if (false == PortalPtr->IsUsingInput)
			{
				GameEngineCore::ChangeLevel(PortalPtr->NextLevelName);
			}

			else
			{
				PortalPtr->InputRenderer->On();
			}


		};

	InteractEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			// 문제 생길 수 있음
			GameEngineActor* thisActor = _this->GetActor();
			Portal* PortalPtr = dynamic_cast<Portal*>(thisActor);


			if (true == PortalPtr->IsUsingInput && GameEngineInput::IsDown(VK_SPACE, thisActor))
			{
				GameEngineCore::ChangeLevel(PortalPtr->NextLevelName);
			}

		};

	InteractEvent.Exit = [](GameEngineCollision* _this, GameEngineCollision* Col)
	{
		GameEngineActor* thisActor = _this->GetActor();
		Portal* PortalPtr = dynamic_cast<Portal*>(thisActor);

		PortalPtr->InputRenderer->Off();

	};

	InteractCollision->CollisionEvent(ContentsCollisionType::PlayerBody, InteractEvent);

}

//  3. init 함수 만들기
//    - 어디로 이동할지, 
//    - 타입이 뭔지 정해줘야함 (입력에 의해 이동할지 EX. 스페이스바 / 접촉시 이동할지 EX. 맵 끝의 트리거)

void Portal::InitPortalData(std::string_view _NextLevelName, bool _IsUsingInput = false)
{
	NextLevelName = _NextLevelName;
	IsUsingInput = _IsUsingInput;
}