#include "pch.h"
#include "GameEffect.h"

ID3D11Device* GameEffect::m_pDevice;
// �R���e�L�X�g�̃|�C���^
ID3D11DeviceContext* GameEffect::m_pContext;

using namespace Effekseer;
using namespace EffekseerRendererDX11;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameEffect::GameEffect(wchar_t path[], float x, float y, float z)
	:cnt(0)
	, flag(false)
{
	// �`��Ǘ��C���X�^���X�̐���
	m_renderer = Renderer::Create(m_pDevice, m_pContext, 256);
	
	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	m_manager = Manager::Create(10);

	// �`����@�̎w��
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	// �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	// ���W�n�̎w��(RH�ŉE��n�ALH�ō���n)
	m_manager->SetCoordinateSystem(CoordinateSystem::RH);

	// �G�t�F�N�g�̓Ǎ�
	m_effect = Effekseer::Effect::Create(m_manager, (EFK_CHAR*)path);
	// �G�t�F�N�g�̍Đ�
	m_handle = m_manager->Play(m_effect, x, y, z);
	//m_manager->SetScale(m_handle, 0.5f, 0.5f, 0.5f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameEffect::~GameEffect()
{
	// �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
	ES_SAFE_RELEASE(m_effect);
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	m_manager->Destroy();
	// �`��p�C���X�^���X��j��
	m_renderer->Destory();
}

/// <summary>
/// ������
/// </summary>
/// <param name="device">�f�o�C�X</param>
/// <param name="context">�R���e�L�X�g</param>
void GameEffect::Initialize(ID3D11Device * device, ID3D11DeviceContext * context)
{
	m_pDevice = device;
	m_pContext = context;
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void GameEffect::Draw(const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)
{
	Effekseer::Matrix44 view44;
	Effekseer::Matrix44 proj44;

	float viewMatrix[4][4]={
		{ view._11,view._12,view._13,view._14 },
		{ view._21,view._22,view._23,view._24 },
		{ view._31,view._32,view._33,view._34 },
		{ view._41,view._42,view._43,view._44 }
	};
	float projMatrix[4][4] = {
		{ proj._11,proj._12,proj._13,proj._14 },
		{ proj._21,proj._22,proj._23,proj._24 },
		{ proj._31,proj._32,proj._33,proj._34 },
		{ proj._41,proj._42,proj._43,proj._44 }
	};


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			view44.Values[i][j] = viewMatrix[i][j];
			proj44.Values[i][j] = projMatrix[i][j];
		}
	}

	// ���e�s��̍X�V
	m_renderer->SetProjectionMatrix(proj44);
	// �J�����s��̍X�V
	m_renderer->SetCameraMatrix(view44);
	// �Đ����̃G�t�F�N�g�̈ړ���(Effekseer::Manager�o�R�ŗl�X�ȃp�����[�^�[���ݒ�ł��܂��B)
	//m_manager->AddLocation(m_handle, Effekseer::Vector3D);
	// �S�ẴG�t�F�N�g�̍X�V
	
	m_manager->Update();

	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();

	cnt++;

	if (cnt > 600) flag = true;
}
