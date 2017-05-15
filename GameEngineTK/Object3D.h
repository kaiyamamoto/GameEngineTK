// 
// 3DObject�̃N���X
// K.Yamamoto
// 
#include <Effects.h>
#include <Model.h>
#include <simplemath.h>
#include <CommonStates.h>

#pragma once
class Object3D
{
private:
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	// �f�o�C�X�̃|�C���^
	static ID3D11Device* m_pDevice;
	// �R���e�L�X�g�̃|�C���^
	static ID3D11DeviceContext* m_pContext;

	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ��]
	DirectX::SimpleMath::Vector3 m_rotate;
	// �X�P�[��
	float m_scale;

public:
	Object3D(const wchar_t* fileName,DirectX::EffectFactory& factory);
	~Object3D();

	// �f�o�C�X�̐ݒ�
	static void SetDevice(ID3D11Device* d3ddevice);
	// �R���e�L�X�g�̐ݒ�
	static void SetContext(ID3D11DeviceContext* d3dcontext);

	// �X�V
	virtual void Update();

	// �`��
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)const;
	
	// �ړ�
	void SetPosition(const DirectX::SimpleMath::Vector3& vec3) { m_position = vec3; }
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	
	// ��]
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { m_rotate = rotate; }
	DirectX::SimpleMath::Vector3 GetRotate() { return m_rotate; }

	// �X�P�[���ύX
	void SetScale(const float& scale) { m_scale = scale; }
};

