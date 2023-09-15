#pragma once

enum class ContentsRenderType
{
	Skyline,
	BackGround,
	Play,
};


enum class ContentsObjectType
{
	BackGround,
	Player,
	Enemy,
};

enum class ContentsCollisionType
{
	PlayerBody,
	PlayerAttack,
	EnemyBody,
	EnemyAttack,
	Interactable,
};