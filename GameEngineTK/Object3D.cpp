// 
// 3DObject�̃N���X
// K.Yamamoto
// 

#include "pch.h"
#include "Object3D.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�ϐ��錾
ID3D11Device*			Object3D::m_pDevice;	// �f�o�C�X�̃|�C���^
ID3D11DeviceContext*	Object3D::m_pContext;	// �R���e�L�X�g�̃|�C���^


Object3D::Object3D(const wchar_t * fileName, DirectX::EffectFactory & factory)
	:m_position(Vector3(0.0f,0.0f,0.0f))
	,m_rotate(Vector3(0.0f,0.0f,0.0f))
	,m_scale(1.0f)
{
	// ���f���̃��[�h
	m_model = Model::CreateFromCMO(m_pDevice, fileName, factory);
}

Object3D::~Object3D()
{
}

// �f�o�C�X�̐ݒ�
void Object3D::SetDevice(ID3D11Device* d3ddevice)
{
	m_pDevice = d3ddevice;
}

// �R���e�L�X�g�̐ݒ�
void Object3D::SetContext(ID3D11DeviceContext * d3dcontext)
{
	m_pContext = d3dcontext;
}

// �X�V
void Object3D::Update()
{
	Matrix scaleMatrix, rotateMatrix, transMatrix;

	// �X�P�[��
	scaleMatrix = Matrix::CreateScale(m_scale);
	// ��]
	rotateMatrix *= Matrix::CreateRotationX(m_rotate.x*XM_2PI);
	rotateMatrix *= Matrix::CreateRotationY(m_rotate.y*XM_2PI);
	rotateMatrix *= Matrix::CreateRotationZ(m_rotate.z*XM_2PI);
	// �ړ�
	transMatrix = Matrix::CreateTranslation(m_position);

	// ���Z
	m_world = scaleMatrix*rotateMatrix*transMatrix;
}

// �`��
void Object3D::Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	m_model->Draw(m_pContext, state, m_world, view, proj);
}
