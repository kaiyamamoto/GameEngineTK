#include "MoveState.h"
#include "JumpingState.h"
#include "OnGroundState.h"
#include <simplemath.h>
#include "..\Input.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace YamagenLib;

MoveState* MoveState::m_instance = nullptr;

/// <summary>
/// ��������
/// </summary>
/// <param name="player"></param>
void MoveState::Enter(Robot & player)
{
	m_time = 0.0f;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="keyTracker">���͂��ꂽ�L�[</param>
/// <returns>���̏�Ԃ�����Ƃ��͏�Ԃ�Ԃ�</returns>
RobotState * MoveState::HandleInput(Robot & robot)
{
	// �W�����v
	if (Input::GetKeyDown(Key::Space)) 		return JumpingState::GetInstance();

	// ���{�ړ�
	if (Input::GetKey(Key::W))		 robot.SetSpeedZ(-0.3f);
	else if (Input::GetKey(Key::S)) robot.SetSpeedZ(0.3f);
	// �ړ����Ă��Ȃ�������߂�
	else {
		robot.SetSpeedZ(0.0f);
		return OnGroundState::GetInstance();
	}
	// �A�j���[�V�����p
	if (robot.GetSpeed().z != 0.0f) m_isWalke = true;
	else m_isWalke = false;

	return nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player"></param>
void MoveState::Update(Robot & robot)
{
	m_time += 0.016;
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Lerp(Vector3(1.0f, 0.0f, 1.0f), Vector3(1.0f, 0.0f, -1.0f), m_time));
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Lerp(Vector3(-1.0f, 0.0f, -1.0f), Vector3(-1.0f, 0.0f, 1.0f), m_time));

	if (m_time == 2.0f) {
		m_time = 0.0f;
	}
}

/// <summary>
/// �o������
/// </summary>
/// <param name="robot"></param>
void MoveState::Exit(Robot & robot)
{
	// �ړ��I��
	robot.SetSpeedZ(0.0f);
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

