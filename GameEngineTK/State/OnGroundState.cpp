#include "OnGroundState.h"
#include "JumpingState.h"
#include "MoveState.h"
#include <simplemath.h>
#include "..\Input.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace YamagenLib;

OnGroundState* OnGroundState::m_instance = nullptr;

/// <summary>
/// ��������
/// </summary>
/// <param name="player"></param>
void OnGroundState::Enter(Robot & player)
{
	m_time = 0.0f;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="keyTracker">���͂��ꂽ�L�[</param>
/// <returns>���̏�Ԃ�����Ƃ��͏�Ԃ�Ԃ�</returns>
RobotState * OnGroundState::HandleInput(Robot & robot)
{
	// �ړ�
	if (Input::GetKey(Key::W))				return MoveState::GetInstance();
	else if (Input::GetKey(Key::S)) 		return MoveState::GetInstance();

	// �W�����v
	if (Input::GetKeyDown(Key::Space)) 		return JumpingState::GetInstance();

	return nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player"></param>
void OnGroundState::Update(Robot & robot)
{
	// ���{��]	�֐���
	Vector3 roteV = Vector3(0.0f, 0.0f, 0.0f);
	if (Input::GetKey(Key::D))	roteV = Vector3(0.0f, -0.01f, 0.0f);
	else if (Input::GetKey(Key::A)) roteV = Vector3(0.0f, 0.01f, 0.0f);
	robot.SetEulerAngle(robot.GetEulerAngle() + roteV);

	if (m_isWalke)
	{
		m_time += 0.016;
		robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Lerp(Vector3(1.0f, 0.0f, 1.0f), Vector3(1.0f, 0.0f, -1.0f), m_time));
		robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Lerp(Vector3(-1.0f, 0.0f, -1.0f), Vector3(-1.0f, 0.0f, 1.0f), m_time));
	}

	if (m_time == 2.0f) {
		m_time = 0.0f;
	}
}

/// <summary>
/// �o������
/// </summary>
/// <param name="robot"></param>
void OnGroundState::Exit(Robot & robot)
{
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

