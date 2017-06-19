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
	DirectX::SimpleMath::Vector3 m_position;
	// ��]�p�i�I�C���[�p�j
	DirectX::SimpleMath::Vector3 m_rotate;
	// ��]�p�i�N�H�[�^�j�I���j
	DirectX::SimpleMath::Quaternion m_rotateQ;
	// �X�P�[��
	float m_scale;
	// �e�̃|�C���^
	Object3D* m_pParent;
	// ��]���N�H�[�^�j�I���Ŏ����Ă��邩�̃t���O
	bool m_useQuternion;
private:	// static 
	// �ǂݍ��ݍς݃��f���R���e�i
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> m_modelArray;

public:		// static
	// ������
	static void Initialize(ID3D11Device* d3ddevice, ID3D11DeviceContext* d3dcontext, DirectX::EffectFactory* effect);

	// �f�o�C�X�̐ݒ�
	static void SetDevice(ID3D11Device* d3ddevice) { m_pDevice = d3ddevice; }
	// �R���e�L�X�g�̐ݒ�
	static void SetContext(ID3D11DeviceContext* d3dcontext) { m_pContext = d3dcontext; }
	// �G�t�F�N�g�t�@�N�g���[�̐ݒ�
	static void SetEffectFactory(DirectX::EffectFactory* effect) { m_pEffectFactory = effect; }

public:
	// �f�t�H���g�R���X�g���N�^
	Object3D();
	Object3D(const wchar_t* fileName);
	Object3D(std::unique_ptr<DirectX::Model> model);
	virtual ~Object3D(){}

	// �t�@�C�����烂�f����ǂݍ���
	DirectX::Model* LoadModelFile(const wchar_t*filename = nullptr);

	// �X�V
	virtual void Update();

	// �`��
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)const;
	
	// ���[���h���W
	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }

	// �ړ�
	void SetPosition(const DirectX::SimpleMath::Vector3& vec3) { m_position = vec3; }
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	
	// ��]�p�p
	void SetRotate(const DirectX::SimpleMath::Vector3& rotation) { m_rotate = rotation*DirectX::XM_2PI; m_useQuternion = false; }
	void SetRotateRadians(const DirectX::SimpleMath::Vector3& rotation) { m_rotate = rotation; m_useQuternion = false; }
	void SetRotateQ(const DirectX::SimpleMath::Quaternion& rotation) { m_rotateQ = rotation; m_useQuternion = true; }
	DirectX::SimpleMath::Vector3 GetRotate() { return m_rotate/DirectX::XM_2PI ; }
	DirectX::SimpleMath::Vector3 GetRotateRadians() { return m_rotate; }

	// �X�P�[���ύX
	void SetScale(const float& scale) { m_scale = scale; }

	// �e�֌W
	void SetParent(Object3D* pObj) { m_pParent = pObj; }
	Object3D* GetParent() { return m_pParent; }
};

