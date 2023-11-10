#include "PreCompile.h"
#include "PlayerCursorSlash.h"
#include "Player.h"

PlayerCursorSlash::PlayerCursorSlash()
{
}

PlayerCursorSlash::~PlayerCursorSlash()
{
}

void PlayerCursorSlash::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");
		{
			GameEngineTexture::Load(FilePath.PlusFilePath("spr_player_cursor_slash.png"));
			GameEngineSprite::CreateSingle("spr_player_cursor_slash.png");
		}
	}

	PlayerCursorSlashRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsRenderType::Play));
	PlayerCursorSlashRenderer->SetSprite("spr_player_cursor_slash.png");
	PlayerCursorSlashRenderer->AutoSpriteSizeOn();

	SlashRot = Player::MainPlayer->PlayerAttackRot;

	PlayerCursorSlashRenderer->Transform.SetWorldRotation({ 0.0f, 0.0f, SlashRot.X });
	PlayerCursorSlashRenderer->Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition() + (Player::MainPlayer->MouseDir * 100));


}

void PlayerCursorSlash::Update(float _Delta)
{
	if (GetLiveTime() < 0.2f)
	{
		PlayerDir Dir = Player::MainPlayer->GetPlayerDirEnum();

		if (PlayerDir::Left == Dir)
		{
			PlayerCursorSlashRenderer->Transform.AddLocalPosition(float4::LEFT * _Delta * 600.0f);
		}

		else if (PlayerDir::Right == Dir)
		{
			PlayerCursorSlashRenderer->Transform.AddLocalPosition(float4::RIGHT * _Delta * 600.0f);
		}

		else if (PlayerDir::LeftDown == Dir || PlayerDir::RightDown == Dir)
		{
			PlayerCursorSlashRenderer->Transform.AddLocalPosition(float4::DOWN * _Delta * 600.0f);
		}

		else if (PlayerDir::LeftUp == Dir || PlayerDir::RightUp == Dir)
		{
			PlayerCursorSlashRenderer->Transform.AddLocalPosition(float4::UP * _Delta * 600.0f);
		}
		
	}
	else
	{
		Death();
	}
}
