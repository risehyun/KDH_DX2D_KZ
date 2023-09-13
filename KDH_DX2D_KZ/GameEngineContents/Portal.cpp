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

	//	1. �ݸ��� �����

	InteractCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Interactable);
	InteractCollision->Transform.SetLocalScale({ 100, 100, 1 });



}

void Portal::Update(float _Delta)
{
	//  2. �÷��̾�� �浹 �̺�Ʈ �����ϱ� 

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

//  3. init �Լ� �����
//    - ���� �̵�����, 
//    - Ÿ���� ���� ��������� (�Է¿� ���� �̵����� EX. �����̽��� / ���˽� �̵����� EX. �� ���� Ʈ����)

void Portal::InitPortalData(std::string_view _NextLevelName, bool _IsUsingInput = false)
{
	NextLevelName = _NextLevelName;
	IsUsingInput = _IsUsingInput;
}