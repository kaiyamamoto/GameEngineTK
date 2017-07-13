// 
// 3DObject�̃N���X
// K.Yamamoto
// 

#include "pch.h"
#include "Object3D.h"

// ���O���
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �萔�錾
const float Object3D::GRAVITY = -1.633f / 60.0f;

// �ÓI�ϐ��錾
ID3D11Device*			Object3D::m_pDevice;	// �f�o�C�X�̃|�C���^
ID3D11DeviceContext*	Object3D::m_pContext;	// �R���e�L�X�g�̃|�C���^
DirectX::EffectFactory* Object3D::m_pEffectFactory;	// �G�t�F�N�g�t�@�N�g���[
// �ǂݍ��ݍς݃��f���R���e�i
map<wstring,unique_ptr<Model>> Object3D::m_modelArray;

/// <summary>
/// �f�t�H���g�R���X�g���N�^
/// </summary>
Object3D::Object3D()
	: m_model(nullptr)
	, m_position(Vector3(0.0f, 0.0f, 0.0f))
	, m_eulerAngles(Vector3(0.0f, 0.0f, 0.0f))
	, m_scale(1.0f)
	, m_pParent(nullptr)
{
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="fileName">���f���̃t�@�C����</param>
/// <param name="factory">�G�t�F�N�g�t�@�N�g���[</param>
Object3D::Object3D(const wchar_t * fileName)
	:Object3D()
{
	// ���f���̃��[�h
	m_model = LoadModelFile(fileName);
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="fileName">���f���|�C���^</param>
Object3D::Object3D(unique_ptr<Model> model)
	:Object3D()
{
	// ���f���̃��[�h
	m_model = model.get();
}

/// <summary>
/// �t�@�C�����烂�f�������[�h
/// </summary>
/// <param name="filename">���f���̃p�X</param>
/// <returns>���f��</returns>
DirectX::Model* Object3D::LoadModelFile(const wchar_t*filename)
{
	assert(m_pEffectFactory);

	// �������O�̃��f����ǂݍ��ݍς݂łȂ���΂Ђ�
	if (m_modelArray.count(filename) == 0)
	{
		// ���f����ǂݍ��݁A�R���e�i�ɓo�^�i�L�[�̓t�@�C�����j
		m_modelArray[filename] = Model::CreateFromCMO(m_pDevice, filename, *m_pEffectFactory);
	}
	return m_modelArray[filename].get();
}

/// <summary>
/// ������
/// </summary>
/// <param name="d3ddevice">�f�o�C�X</param>
/// <param name="d3dcontext">�R���e�L�X�g</param>
void Object3D::Initialize(ID3D11Device * d3ddevice, ID3D11DeviceContext * d3dcontext, EffectFactory* effect)
{
	// �f�o�C�X�̐ݒ�
	SetDevice(d3ddevice);
	// �R���e�L�X�g�̐ݒ�
	SetContext(d3dcontext);
	// �G�t�F�N�g�t�@�N�g���[
	SetEffectFactory(effect);
}

void Object3D::LoadModel(const wchar_t * fileName)
{
	m_model = LoadModelFile(fileName);

}


/// <summary>
/// �X�V
/// </summary>
void Object3D::Update()
{
	Matrix scaleMatrix, rotateMatrix, transMatrix;

	// �X�P�[��
	scaleMatrix = Matrix::CreateScale(m_scale);

	// ��]�s��
	if (m_useQuternion)
	{// �N�H�[�^�j�I�������]�s����v�Z
		rotateMatrix = Matrix::CreateFromQuaternion(m_rotateQuaternion);
	}
	else
	{// �I�C���[�p�����]�s����v�Z�iZ��X��Y�j
		rotateMatrix *= Matrix::CreateRotationZ(m_eulerAngles.z);
		rotateMatrix *= Matrix::CreateRotationX(m_eulerAngles.x);
		rotateMatrix *= Matrix::CreateRotationY(m_eulerAngles.y);
	}
	// �ړ�
	transMatrix = Matrix::CreateTranslation(m_position);
	// ���Z
	m_world = scaleMatrix*rotateMatrix*transMatrix;
	// �e�̍s���������
	if (m_pParent){
		m_world *= m_pParent->GetWorld();
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="state">�R�����X�e�[�g</param>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Object3D::Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	m_model->Draw(m_pContext, state, m_world, view, proj);
}
