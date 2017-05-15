
// Camera �N���X

#pragma once
#include <simplemath.h>

class Camera
{
protected:
	DirectX::SimpleMath::Matrix		m_view;		// �r���[�s��
	DirectX::SimpleMath::Vector3	m_eyePos;	// �J�����̈ʒu
	DirectX::SimpleMath::Vector3	m_refPos;	// �����_
	DirectX::SimpleMath::Vector3	m_upVec;	// ������x�N�g��
	DirectX::SimpleMath::Matrix		m_proj;		// �ˉe�s��
	float							m_fovY;		// ������������p(�c�̎���)
	float							m_aspect;	// ��ʂ̏c���䗦
	float							m_nearClip;	// ��O�̕\�����E
	float							m_farClip;	// ���̕\�����E

public:
	Camera(int screenWidth, int screenHeight);			// �R���X�g���N�^
	virtual ~Camera();							// ���z�f�X�g���N�^

	void Update();		// �X�V
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_view; }
	DirectX::SimpleMath::Matrix GetProjMatrix() const { return m_proj; }
	void SetEyePos(const DirectX::SimpleMath::Vector3 &eyePos) { m_eyePos = eyePos; }
	void SetRefPos(const DirectX::SimpleMath::Vector3 &refPos) {m_refPos = refPos;}
	void SetUpVecPos(const DirectX::SimpleMath::Vector3 &upVec) { 
		m_upVec = upVec; 
		m_upVec.Normalize();
	}
};

