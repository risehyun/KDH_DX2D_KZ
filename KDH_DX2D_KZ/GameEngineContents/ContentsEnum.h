#pragma once

enum class ContentsRenderType
{
	Skyline,
	BackGround,
	Play,
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
	EnemyBody,
	EnemyAttack,
	EnemyDetect,
	Interactable,
};