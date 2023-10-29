#include "PreCompile.h"
#include "LaserGroup.h"

LaserGroup::LaserGroup()
{
}

LaserGroup::~LaserGroup()
{
}

void LaserGroup::InitLaserGroupData(int _LaserCount, float4 _InitPos, float _XDistance, bool _UseLongType, bool _UseMoving)
{
	IsUseMoving = _UseMoving;

	for (int i = 0; i < _LaserCount; i++)
	{
		std::shared_ptr<Laser> Object = GetLevel()->CreateActor<Laser>();
		Object->InitLaserData(_UseLongType);
		Object->Transform.SetLocalPosition({ _InitPos.X + _XDistance * i, _InitPos.Y });
		AllLaser.push_back(Object);
	}

	if (true == IsUseMoving)
	{
		GroupLastCount = AllLaser.size();
	}
}

void LaserGroup::Start()
{
}

void LaserGroup::Update(float _Delta)
{
	if (IsUseMoving)
	{
		if (AllLaser[GroupLastCount - 1]->Transform.GetLocalPosition().X >= 1200.0f)
		{
			MoveDir = { -1.0f, 0.0f };
		}

		if (AllLaser[0]->Transform.GetLocalPosition().X < 660.0f)
		{
			MoveDir = { 1.0f, 0.0f };
		}

		for (int i = 0; i < GroupLastCount; i++)
		{
			AllLaser[i]->Transform.AddLocalPosition({ MoveDir * _Delta * 200.0f });
		}

	}
}
