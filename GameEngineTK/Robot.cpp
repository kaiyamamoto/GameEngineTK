// 
// Robot�̃N���X
// K.Yamamoto
// 

#include "Robot.h"
#include"State\OnGroundState.h"

// ���O���
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Robot::Robot()
	:Object3D()
	,m_robotParts(Parts::length)
	,m_state(OnGroundState::GetInstance())	// ������Ԍ�ŕύX
	,m_speed(Vector3(0.0f,0.0f,0.0f))
	,m_acceleSpeed(Vector3(0.0f,0.05f,0.0f))
{
	// ������
	Initialize();
}

// ������
void Robot::Initialize()
{
	// �I�u�W�F�N�g�̓ǂݍ���
	m_robotParts[BODY] = std::make_unique<Object3D>(L"Resources\\body.cmo");
	m_robotParts[HEAD] = std::make_unique<Object3D>(L"Resources\\head.cmo");
	m_robotParts[RIGHTARM] = std::make_unique<Object3D>(L"Resources\\missile.cmo");
	m_robotParts[LEFTARM] = std::make_unique<Object3D>(L"Resources\\missile.cmo");
	m_robotParts[RIGHTLEG] = std::make_unique<Object3D>(L"Resources\\leg.cmo");
	m_robotParts[LEFTLEG] = std::make_unique<Object3D>(L"Resources\\leg.cmo");

	// �e�q�֌W
	// �S�p�[�cBODY�̎q�ɂȂ�
	m_robotParts[BODY]->SetParent(this);
	m_robotParts[HEAD]->SetParent(m_robotParts[BODY].get());
	m_robotParts[RIGHTARM]->SetParent(m_robotParts[BODY].get());
	m_robotParts[LEFTARM]->SetParent(m_robotParts[BODY].get());
	m_robotParts[RIGHTLEG]->SetParent(m_robotParts[BODY].get());
	m_robotParts[LEFTLEG]->SetParent(m_robotParts[BODY].get());

	// �T�C�Y�ݒ�
	this->SetScale(0.5f);

	// �S�̓I�ȍ��W����
	m_robotParts[HEAD]->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
	m_robotParts[RIGHTARM]->SetPosition(Vector3(2.0f, 2.0f, 0.0f));
	m_robotParts[LEFTARM]->SetPosition(Vector3(-2.0f, 2.0f, 0.0f));
	m_robotParts[RIGHTLEG]->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	m_robotParts[LEFTLEG]->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

/// <summary>
/// �`��
/// </summary>
/// <param name="state"></param>
/// <param name="view"></param>
/// <param name="proj"></param>
void Robot::Draw(const DirectX::CommonStates & state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	for (auto itr = m_robotParts.begin(); itr != m_robotParts.end(); ++itr) {
		(*itr)->Draw(state, view, proj);
	}
}

/// <summary>
/// �X�V
/// </summary>
void Robot::Update()
{
	// ���̍X�V
	this->Object3D::Update();
	// ���f���̍s��X�V
	Calc();

	// �ړ�
	m_position += m_speed;
}

/// <summary>
/// �s��̍X�V
/// </summary>
void Robot::Calc()
{
	for (auto itr = m_robotParts.begin(); itr != m_robotParts.end(); ++itr)
	{
		(*itr)->Update();
	}
}