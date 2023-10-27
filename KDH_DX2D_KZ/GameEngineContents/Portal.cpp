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

	//	1. �ݸ��� �����

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

			else
			{
				PortalPtr->InputRenderer->On();
			}


		};

	InteractEvent.Stay = [](GameEngineCollision* _this, GameEngineCollision* Col)
		{
			// ���� ���� �� ����
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

//  3. init �Լ� �����
//    - ���� �̵�����, 
//    - Ÿ���� ���� ��������� (�Է¿� ���� �̵����� EX. �����̽��� / ���˽� �̵����� EX. �� ���� Ʈ����)

void Portal::InitPortalData(std::string_view _NextLevelName, bool _IsUsingInput = false)
{
	NextLevelName = _NextLevelName;
	IsUsingInput = _IsUsingInput;
}