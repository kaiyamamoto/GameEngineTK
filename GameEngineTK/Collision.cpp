#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ３点から三角形を計算（反時計回りに指定）
/// </summary>
/// <param name="_p0">点</param>
/// <param name="_p1">点</param>
/// <param name="_p2">点</param>
/// <param name="_triangle">結果出力する三角形</param>
void Triangle::ComputeTriangle(const Vector3 & _p0, const Vector3 & _p1, const Vector3 & _p2, Triangle * _triangle)
{
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// 法線ベクトル計算
	Vector3 P0_P1 = _triangle->P1 - _triangle->P0;
	Vector3 P1_P2 = _triangle->P2 - _triangle->P1;

	// 外積で2辺に直角なベクトル算出
	_triangle->Normal = P0_P1.Cross(P1_P2);
	// 単位ベクトルにする
	_triangle->Normal.Normalize();
}
