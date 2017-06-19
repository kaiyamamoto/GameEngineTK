#include "PlayerRobot.h"
#include "State\StandingState.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerRobot::PlayerRobot()
	:Robot()
{
	// �����Ă�����
	m_state = StandingState::GetInstance();
	m_state->Enter(*this);
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
	// �X�V
	m_state->Update(*this);

	RobotState* localstate = m_state->HandleInput(*this);
	if (localstate != nullptr) {
		m_state->Exit(*this);
		m_state = localstate;
		// ��������
		m_state->Enter(*this);
	}
	// ���{�b�g�̍X�V
	this->Robot::Update();
}


