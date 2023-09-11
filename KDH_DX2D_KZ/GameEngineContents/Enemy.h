#pragma once
#include "Character.h"


enum class EnemyState
{
	Idle,
	Run,
	Jump,
	Fall,
	PostCrouch,
	PreCrouch,
	Roll,
	Attack,
	Dash,
	Default,
};

enum class EnemyDir
{
	Right,
	Left,
	Default,
};



class Enemy : public Character
{





};

