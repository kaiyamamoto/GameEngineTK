#include "MoveState.h"
#include "JumpingState.h"
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
	Update(robot);

	// ���{��]	�֐���
	Vector3 roteV = Vector3(0.0f, 0.0f, 0.0f);
	if		(Input::GetKey(Key::D))	  roteV = Vector3(0.0f, -0.01f, 0.0f);
	else if (Input::GetKey(Key::A)) roteV = Vector3(0.0f, 0.01f, 0.0f);
	robot.SetEulerAngle(robot.GetEulerAngle() + roteV);

	// ���{�ړ�	�֐���
	Vector3 moveV = Vector3(0.0f, 0.0f, 0.0f);
	if		(Input::GetKey(Key::W))		 moveV = Vector3(0.0f, 0.0f, -0.1f);

	else if (Input::GetKey(Key::S)) moveV = Vector3(0.0f, 0.0f, +0.1f);

	if (moveV != Vector3::Zero) m_isWalke = true;
	else m_isWalke = false;

	// �ړ���]	�֐���
	Matrix rotmat = Matrix::Identity;
	rotmat *= Matrix::CreateRotationY(robot.GetEulerAngleRadians().y);
	moveV = Vector3::TransformNormal(moveV, rotmat);
	robot.SetPosition(robot.GetPosition() + moveV);

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
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

