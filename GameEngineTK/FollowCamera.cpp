#include "pch.h"
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float FollowCamera::CAMERA_DISTANCE = 10.0f;		// �J�����̋���

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pObj">�Ǐ]����I�u�W�F�N�g</param>
/// <param name="screenWidth">��ʂ̕�</param>
/// <param name="screenHeight">��ʂ̍���</param>
/// <param name="distance=5.0f">�J�����Ƃ̋���</param>
FollowCamera::FollowCamera(Object3D* pObj, int screenWidth, int screenHeight)
	:m_pObject(pObj)
	, Camera(screenWidth, screenHeight)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FollowCamera::~FollowCamera()
{

}

/// <summary>
/// �X�V
/// </summary>
void FollowCamera::Update()
{
	// ���_�A�Q�Ɠ_
	Vector3 eyepos, refpos;

	//Vector3 objUpPos;

	//// �J�������W�v�Z
	//objUpPos = m_pObject->GetPosition() + Vector3(0.0f, 0.2f, 0.0f);

	//// �J�������W�ւ̍���
	//Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);

	//// �J�����̎��_�����̋t�����ɉ�]
	//Matrix rotmat = Matrix::CreateRotationY(m_pObject->GetRotateRadians().y);
	//cameraV = Vector3::TransformNormal(cameraV, rotmat);
	//
	//// �G
	//eyepos = objUpPos + cameraV * 0.05f;
	//// �Q�Ɠ_���v�Z
	//refpos = eyepos + cameraV;

	// �I�u�W�F�N�g��Ǐ]
	refpos = m_pObject->GetPosition() + Vector3(0.0f, 2.0f, 0.0f);
	// �J�������W�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);

	// �J�����̎��_�����̋t�����ɉ�]
	Matrix rotmat = Matrix::CreateRotationY(m_pObject->GetEulerAngleRadians().y);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	// �J�������W�v�Z
	eyepos = refpos + cameraV;

	// �S���R�p ==================================
	// ���_�����݈ʒu������
	eyepos = m_eyePos + (eyepos - m_eyePos)*0.05f;
	// �Q�Ɠ_�����݈ʒu������
	refpos = m_refPos + (refpos - m_refPos)*0.2f;
	// ===========================================

	// �J�����̍X�V
	SetEyePos(eyepos);	// �J�����ʒu
	SetRefPos(refpos);	// �Q�Ɠ_
	SetUpVecPos(Vector3(0, 1, 0));		// ������x�N�g��

	// ���N���X�̃J�����̍X�V
	this->Camera::Update();
}
