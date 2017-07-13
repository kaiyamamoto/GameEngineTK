// 
// 3DObject�̃N���X
// K.Yamamoto
// 
#pragma once
#include <Effects.h>
#include <Model.h>
#include <simplemath.h>
#include <CommonStates.h>
#include <map>

static const float PI = 3.141592;

using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Quaternion;

class Object3D
{
public :	// �萔
	static const float GRAVITY;	//�d��

protected:
	// ���f��
	DirectX::Model* m_model;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	// �f�o�C�X�̃|�C���^
	static ID3D11Device* m_pDevice;
	// �R���e�L�X�g�̃|�C���^
	static ID3D11DeviceContext* m_pContext;
	// �G�t�F�N�g�t�@�N�g���[
	static DirectX::EffectFactory* m_pEffectFactory;
	// ���W
	Vector3 m_position;
	// ��]�p�i�I�C���[�p�j
	Vector3 m_eulerAngles;
	// ��]�p�i�N�H�[�^�j�I���j
	Quaternion m_rotateQuaternion;
	// �X�P�[��
	Vector3 m_scale;
	// �e�̃|�C���^
	Object3D* m_pParent;
	// ��]���N�H�[�^�j�I���Ŏ����Ă��邩�̃t���O
	bool m_useQuternion;

private:	// �ÓI�ϐ�
	// �ǂݍ��ݍς݃��f���R���e�i
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> m_modelArray;

public:		// static�֐�
	// ������
	static void Initialize(ID3D11Device* d3ddevice, ID3D11DeviceContext* d3dcontext, DirectX::EffectFactory* effect);
	// �f�o�C�X�̐ݒ�
	static void SetDevice(ID3D11Device* d3ddevice) { m_pDevice = d3ddevice; }
	// �R���e�L�X�g�̐ݒ�
	static void SetContext(ID3D11DeviceContext* d3dcontext) { m_pContext = d3dcontext; }
	// �G�t�F�N�g�t�@�N�g���[�̐ݒ�
	static void SetEffectFactory(DirectX::EffectFactory* effect) { m_pEffectFactory = effect; }
public:
	// �R���X�g���N�^
	Object3D();
	Object3D(const wchar_t* fileName);
	Object3D(std::unique_ptr<DirectX::Model> model);
	// �f�X�g���N�^
	virtual ~Object3D(){}

	// �t�@�C�����烂�f����ǂݍ���
	DirectX::Model* LoadModelFile(const wchar_t*filename = nullptr);

	// ���f���̃��[�h
	void LoadModel(const wchar_t * fileName);

	// �X�V
	virtual void Update();

	// �`��
	void Draw(const DirectX::CommonStates& state, const Matrix& view, const Matrix& proj)const;

	// ���[���h���W
	Matrix GetWorld()						{ return m_world;	 }
	void SetWorld(const Matrix& mat) { m_world = mat; }
	
	// �ړ�
	void SetPosition(const Vector3& vec3)	{ m_position = vec3; }
	Vector3 GetPosition()					{ return m_position; }
	
	// ��]�p�p
	void SetEulerAngle(const Vector3& rotation)			{ m_eulerAngles = rotation*DirectX::XM_2PI; m_useQuternion = false; }
	void SetEulerAngleRadians(const Vector3& rotation)	{ m_eulerAngles = rotation; m_useQuternion = false; }
	void SetRotation(const Quaternion& rotation)		{ m_rotateQuaternion = rotation; m_useQuternion = true; }
	Vector3 GetEulerAngle()								{ return m_eulerAngles / DirectX::XM_2PI; }
	Vector3 GetEulerAngleRadians()						{ return m_eulerAngles; }
	const Quaternion& GetRotation()						{ return m_rotateQuaternion; }

	// �X�P�[���ύX
	void SetScale(const float& scale) { m_scale = Vector3(scale); }
	void SetScale(const Vector3& scale) { m_scale = scale; }
	Vector3 GetScale() { return m_scale; }

	// �e�֌W
	void SetParent(Object3D* pObj) { m_pParent = pObj; }
	Object3D* GetParent() { return m_pParent; }
};

