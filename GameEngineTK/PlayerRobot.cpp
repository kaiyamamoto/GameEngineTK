#include "PlayerRobot.h"
#include "State\OnGroundState.h"
#include "State\RobotCommonState.h"
#include "Input.h"
#include "Stage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace YamagenLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerRobot::PlayerRobot()
	:Robot()
	, m_FireFlag(false)
{
	// �����Ă�����
	m_state = OnGroundState::GetInstance();
	m_state->Enter(*this);

	m_CollisionNodeBody.Initialize();
	// �x�[�X�p�[�c�ɂԂ牺����
	m_CollisionNodeBody.SetParent(this);
	// �x�[�X�p�[�c����̃I�t�Z�b�g
	m_CollisionNodeBody.SetTrans(Vector3(0, 1.0f, 0));
	// �����蔻��̔��a
	m_CollisionNodeBody.SetLocalRadius(2.0f);

	m_CollisionNode.Initialize();
	// ���@�ɒ�����
	m_CollisionNode.SetParent(m_robotParts[Parts::RIGHTARM].get());
	// ����p�[�c����̃I�t�Z�b�g
	m_CollisionNode.SetTrans(Vector3(0, 0.0f, -1.5f));
	// �����蔻��̔��a
	m_CollisionNode.SetLocalRadius(1.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerRobot::~PlayerRobot()
{
}

/// <summary>
/// �X�V
/// </summary>
void PlayerRobot::Update()
{
	// ���ʏ���
	RobotCommonState::GetInstance()->HandleInput(*this);
	// �J�ڏ���
	// ���͎���
	RobotState* collisionState = this->Robot::CollisionCheck();
	RobotState* localstate = m_state->HandleInput(*this);
	
	if (collisionState) localstate = collisionState;

	// �����蔻�����
	if (localstate != nullptr) {
		m_state->Exit(*this);
		m_state = localstate;
		// ��������
		m_state->Enter(*this);
	}
	// ��Ԃ̍X�V
	m_state->Update(*this);

	// �e
	if (Input::GetKeyDown(Key::RightShift)) FireBullet();

	// ���{�b�g�̍X�V
	this->Robot::Update();

	// �����蔻��X�V
	// �����蔻��̍X�V
	m_CollisionNodeBody.Update();
	m_CollisionNode.Update();

	// �e�ۂ��i�ޏ���
	if (m_FireFlag)
	{
		// ���@�̍��W���ړ�
		Vector3 pos = m_robotParts[Parts::RIGHTARM]->GetPosition();
		pos += m_BulletVel;
		m_robotParts[Parts::RIGHTARM]->SetPosition(pos);
	}
}

/// <summary>
/// �@�`��
/// </summary>
/// <param name="state">�X�e�[�g</param>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void PlayerRobot::Draw(const DirectX::CommonStates & state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	// ���̕`��
	this->Robot::Draw(state, view, proj);

	m_CollisionNode.Draw(state, view, proj);
	m_CollisionNodeBody.Draw(state, view, proj);
	// �f�o�b�O

	// state�̕\��
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), m_state->GetStateName(), XMFLOAT2(0.0f, 0.0f));
	spriteBatch->End();
}

/// <summary>
/// ����
/// </summary>
void PlayerRobot::FireBullet()
{
	if (m_FireFlag)
	{
		ResetBullet();
		return;
	}

	// ���[���h�s����擾
	Matrix worldm = m_robotParts[Parts::RIGHTARM]->GetWorld();

	Vector3 scale;	// ���[���h�X�P�[�����O
	Quaternion rotation;	// ���[���h��]
	Vector3 translation;	// ���[���h���W

							// ���[���h�s�񂩂�e�v�f�����o��
	worldm.Decompose(scale, rotation, translation);

	// �e�q�֌W���������ăp�[�c��Ɨ�������
	m_robotParts[Parts::RIGHTARM]->SetParent(nullptr);
	m_robotParts[Parts::RIGHTARM]->SetScale(scale);
	m_robotParts[Parts::RIGHTARM]->SetRotation(rotation);
	m_robotParts[Parts::RIGHTARM]->SetPosition(translation);

	// �e�̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.5f);
	// �e�̌����ɍ��킹�Đi�s��������]
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_FireFlag = true;
}

/// <summary>
/// �e���Z�b�g
/// </summary>
void PlayerRobot::ResetBullet()
{
	m_robotParts[Parts::RIGHTARM]->SetParent(
		m_robotParts[Parts::BODY].get());

	m_robotParts[Parts::RIGHTARM]->SetPosition(
		Vector3(2.0f, 2.0f, 0.0f));
	m_robotParts[Parts::RIGHTARM]->SetScale(1.0f);
	m_robotParts[Parts::RIGHTARM]->SetEulerAngleRadians(Vector3(0, 0, 0));

	m_FireFlag = false;
}

/// <summary>
/// �����������̏���
/// </summary>
/// <param name="tag">���������I�u�W�F�N�g�̎��</param>
void PlayerRobot::OnCollisionEnter(const Object3D& obj)
{
	// �^���̎擾  
	const type_info& id = typeid(obj);

	// ���������̂��X�e�[�W�̎�
	if (id == typeid(LandShape)) {
		// ��ɋ���Ƃ�
		if (m_position.y > obj.GetPosition().y) {
			// �n�ʂ̏�ɂ����ԂɂȂ�
			m_state = OnGroundState::GetInstance();
		}
	}
}
