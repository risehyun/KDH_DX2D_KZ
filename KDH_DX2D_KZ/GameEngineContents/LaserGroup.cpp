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
		GroupLastCount = static_cast<int>(AllLaser.size());
	}
}

void LaserGroup::Start()
{
}

void LaserGroup::Update(float _Delta)
{
	if (IsUseMoving)
	{

		for (int i = 0; i < GroupLastCount; i++)
		{
			if (AllLaser[i]->Transform.GetLocalPosition().X >= 1200.0f)
			{
				AllLaser[i]->MoveDir = { -1.0f, 0.0f };
			}

			if (AllLaser[i]->Transform.GetLocalPosition().X < 660.0f)
			{
				AllLaser[i]->MoveDir = { 1.0f, 0.0f };
			}
		}

		for (int i = 0; i < GroupLastCount; i++)
		{
			AllLaser[i]->Transform.AddLocalPosition({ AllLaser[i]->MoveDir * _Delta * 200.0f });
		}


	}
}
