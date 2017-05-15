#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary> �R���X�g���N�^ </summary>
Camera::Camera(int screenWidth, int screenHeight)
	: m_view(Matrix::Identity)								// �r���[�s��
	, m_eyePos(Vector3(0.0f, 0.0f, 0.0f))					// �J�����̈ʒu
	, m_refPos(Vector3(0.0f, 0.0f, 0.0f))					// �����_
	, m_upVec(Vector3(0.0f, 1.0f, 0.0f))					// ������x�N�g��
	, m_proj(Matrix::Identity)								// �ˉe�s��
	, m_fovY(XMConvertToRadians(60.0f))						// ������������p(�c�̎���)
	, m_aspect(float(screenWidth) / float(screenHeight))	// ��ʂ̏c���䗦
	, m_nearClip(0.1f)										// ��O�̕\�����E
	, m_farClip(1000.0f)									// ���̕\�����E
{
	m_upVec.Normalize();
}

/// <summary> �f�X�g���N�^ </summary>
Camera::~Camera()
{
}

/// <summary> �X�V </summary>
void Camera::Update()
{
	// �r���[�s����Z�o����
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

}
