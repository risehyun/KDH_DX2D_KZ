#pragma once

enum class ContentsRenderType
{
	Skyline,
	BackGround,
	Play,
	PlayFront,
	UI,
};


enum class ContentsObjectType
{
	BackGround,
	Player,
	Enemy,
	UI,
};

enum class ContentsCollisionType
{
	PlayerBody,
	PlayerAttack,
	PlayerParrying,
	PlayerDash,
	EnemyBody,
	EnemyAttack,
	EnemyDetect,
	BossGrenade,
	BossGrenadeArea,
	BossBombArea,
	BossLaser,
	Interactable,
};