#include "InAirState.h"
#include "JumpingState.h"
#include "MoveState.h"
#include <simplemath.h>
#include "OnGroundState.h"
#include "..\Input.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace YamagenLib;

InAirState* InAirState::m_instance = nullptr;

/// <summary>
/// ��������
/// </summary>
/// <param name="player"></param>
void InAirState::Enter(Robot & player)
{
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="keyTracker">���͂��ꂽ�L�[</param>
/// <returns>���̏�Ԃ�����Ƃ��͏�Ԃ�Ԃ�</returns>
RobotState * InAirState::HandleInput(Robot & robot)
{
	MoveState::GetInstance()->HandleInput(robot);

	// �W�����v(��)
	if (Input::GetKeyDown(Key::Space)) 		return JumpingState::GetInstance();


	return nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player"></param>
void InAirState::Update(Robot & robot)
{
	// �d�͂𔽉f
	float speedY = robot.GetSpeed().y;
	speedY += Object3D::GRAVITY;
	robot.SetSpeedY(speedY);
}

/// <summary>
/// �o������
/// </summary>
/// <param name="robot"></param>
void InAirState::Exit(Robot & robot)
{
	robot.SetSpeedY(0.0f);
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

