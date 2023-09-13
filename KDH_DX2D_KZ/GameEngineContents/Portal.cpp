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

	//	1. 콜리전 만들기

	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->Transform.SetLocalScale({ 100, 100, 1 });



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


		};

	InteractEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			GameEngineActor* thisActor = _this->GetActor();
			Portal* PortalPtr = dynamic_cast<Portal*>(thisActor);


			if (true == PortalPtr->IsUsingInput && GameEngineInput::IsDown(VK_SPACE))
			{
				GameEngineCore::ChangeLevel(PortalPtr->NextLevelName);
			}

		};

	InteractCollision->CollisionEvent(ContentsCollisionType::Player, InteractEvent);

}

//  3. init 함수 만들기
//    - 어디로 이동할지, 
//    - 타입이 뭔지 정해줘야함 (입력에 의해 이동할지 EX. 스페이스바 / 접촉시 이동할지 EX. 맵 끝의 트리거)

void Portal::InitPortalData(std::string_view _NextLevelName, bool _IsUsingInput = false)
{
	NextLevelName = _NextLevelName;
	IsUsingInput = _IsUsingInput;
}