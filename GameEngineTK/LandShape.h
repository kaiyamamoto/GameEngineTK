//--------------------------------------------------------------------------------------
// �t�@�C����: LandShape
// �쐬��:
// �쐬��:
// ����:�n�`������
//--------------------------------------------------------------------------------------

#pragma once

#include "LandShapeData.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>
#include <map>
//
#include "Camera.h"
#include "Object3D.h"
#include "Collision.h"



// ���p�f�[�^�������p�\����
struct LandShapeCommonDef
{
	// �f�o�C�X(DirectX11)
	ID3D11Device* pDevice;
	// �f�o�C�X�R���e�L�X�g(DirectX11)
	ID3D11DeviceContext* pDeviceContext;
	// �J����
	Camera* pCamera;

	LandShapeCommonDef()
	{
		pDevice = nullptr;
		pDeviceContext = nullptr;
		pCamera = nullptr;
	}
};

// ���p�f�[�^
class LandShapeCommon
{
	// LandShape�N���X���烁���o�ϐ��ɃA�N�Z�X�ł���悤�ɂ���
	friend class LandShape;
public:
	// �f�o�b�O�\���p�̍ő咸�_��
	static const size_t BatchSize = 6144;
	// �R���X�g���N�^
	LandShapeCommon(LandShapeCommonDef def);
	// �f�X�g���N�^
	~LandShapeCommon();
protected:
	// ���ʃJ����
	Camera* m_pCamera;
	// �R�����X�e�[�g�ւ̃|�C���^
	std::unique_ptr<DirectX::CommonStates>	m_pStates;
	// �G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory>	m_pEffectFactory;
	// �x�[�V�b�N�G�t�F�N�g�ւ̃|�C���^
	std::unique_ptr<DirectX::BasicEffect>	m_pEffect;
	// �v���~�e�B�u�o�b�`�ւ̃|�C���^
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>>	m_pPrimitiveBatch;
	// ���̓��C�A�E�g�ւ̃|�C���^
	ID3D11InputLayout*	m_pInputLayout;
	// �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
	ID3D11DeviceContext*	m_pDeviceContext;
};


// �n�`������
class LandShape:public Object3D
{
public:
	// �G�t�F�N�g�t�@�N�g������
	static void InitializeCommon(LandShapeCommonDef def);

	// �R���X�g���N�^
	LandShape() ;
	// ������
	void Initialize(const std::wstring& filename_bin, const std::wstring& filename_cmo);
	// ���[���h�s��̌v�Z
	void Update();
	// �f�o�b�O�`��
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj);
	// ���C�e�B���O�J�b�g
	void DisableLighting();

	bool IntersectSphere(const Sphere& sphere, DirectX::SimpleMath::Vector3* reject) const ;
	bool IntersectSegment(const Segment& segment, DirectX::SimpleMath::Vector3* inter)const ;
	bool IntersectSegmentFloor(const Segment& segment, DirectX::SimpleMath::Vector3* inter)const ;

protected:
	// ���ʃf�[�^
	static std::unique_ptr<LandShapeCommon> s_pCommon;
	// �n�`������f�[�^�}�b�v
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> s_dataarray;

	// �n�`������f�[�^
	const LandShapeData* m_pData;
	// ���[���h�����f���s��
	DirectX::SimpleMath::Matrix m_WorldLocal;
};