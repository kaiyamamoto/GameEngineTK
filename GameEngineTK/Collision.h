/// <summary>
/// 衝突判定ライブラリ
/// </summary>
#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>

// 球
class Sphere
{
public:
	// 中心座標
	DirectX::SimpleMath::Vector3 center;
	// 半径
	float radius;
	// コンストラクタ
	Sphere() :radius(1.0f) {}
};

// 線分
class Segment
{
public:
	// 始点座標
	DirectX::SimpleMath::Vector3 start;
	// 終点座標
	DirectX::SimpleMath::Vector3 end;
};

// 法線付き三角形（反時計回りが表面）
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// 法線ベクトル

	// ３点から三角形を計算（反時計回りに指定）
	static void ComputeTriangle(const DirectX::SimpleMath::Vector3& _p0, const DirectX::SimpleMath::Vector3& _p1, const DirectX::SimpleMath::Vector3& _p2, Triangle* _triangle);
};