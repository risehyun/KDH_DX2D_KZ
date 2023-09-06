#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
{
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.LocalWorldMatrix * TransData.ParentMatrix;
	}



	// TransData.WorldMatrix.ArrVector[3]

	// 월드 크기
	// 월드 회전
	// 월드 위치
	// TransData.WorldMatrix

	// 월드 크기
	// 월드 회전
	// 월드 위치
	// TransData.WorldMatrix

	// TransData.WorldMatrix<= 내부에서 
	// TransData.WorldMatrix

	// 로컬이랑 월드를 계산한적이 없어요.



	// ColData.AABB

	CalChilds();
}

void GameEngineTransform::CalculationViewAndProjection(const TransformData& _Transform)
{
	CalculationViewAndProjection(_Transform.ViewMatrix, _Transform.ProjectionMatrix);
}

void GameEngineTransform::CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	TransData.ViewMatrix = _View;
	TransData.ProjectionMatrix = _Projection;
	TransData.WorldViewProjectionCalculation();
}

void GameEngineTransform::CalChilds()
{
	if (0 == Childs.size())
	{
		return;
	}

	for (GameEngineTransform* Trans : Childs)
	{
		Trans->TransformUpdate();
	}
}

bool GameEngineTransform::Collision(const CollisionParameter& _Data)
{
	DirectX::BoundingSphere SPHERE;
	DirectX::BoundingBox AABB;
	DirectX::BoundingOrientedBox OBB;

	//SPHERE.Center;
	//SPHERE.Radius;

	//AABB.Center;
	//AABB.Extents;

	bool Check = SPHERE.Intersects(AABB);

	return true;
}