#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R�_����O�p�`���v�Z�i�����v���Ɏw��j
/// </summary>
/// <param name="_p0">�_</param>
/// <param name="_p1">�_</param>
/// <param name="_p2">�_</param>
/// <param name="_triangle">���ʏo�͂���O�p�`</param>
void Triangle::ComputeTriangle(const Vector3 & _p0, const Vector3 & _p1, const Vector3 & _p2, Triangle * _triangle)
{
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// �@���x�N�g���v�Z
	Vector3 P0_P1 = _triangle->P1 - _triangle->P0;
	Vector3 P1_P2 = _triangle->P2 - _triangle->P1;

	// �O�ς�2�ӂɒ��p�ȃx�N�g���Z�o
	_triangle->Normal = P0_P1.Cross(P1_P2);
	// �P�ʃx�N�g���ɂ���
	_triangle->Normal.Normalize();
}
