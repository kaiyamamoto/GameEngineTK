#include "JumpingState.h"
#include "StandingState.h"
#include <simplemath.h>

using namespace DirectX::SimpleMath;

JumpingState* JumpingState::m_instance = nullptr;

/// <summary>
/// ��������
/// </summary>
/// <param name="player"></param>
void JumpingState::Enter(Robot & robot)
{
	Vector3 speed = robot.GetSpeed();
	speed.y += 0.5f;
	robot.SetSpeed(speed);
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="keyTracker">���͂��ꂽ�L�[</param>
/// <returns>���̏�Ԃ�����Ƃ��͏�Ԃ�Ԃ�</returns>
RobotState * JumpingState::HandleInput(Robot & robot)
{
	// �X�^���f�B���O��Ԃ̏���
	StandingState::GetInstance()->HandleInput(robot);

	Vector3 pos = robot.GetPosition();

	if (pos.y <= 1.0f) {		
		Vector3 speed = robot.GetSpeed();
		speed.y = 0.0f;
		robot.SetSpeed(speed);
		// �W�����v�I��
		return StandingState::GetInstance();
	}
	return nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player"></param>
void JumpingState::Update(Robot & robot)
{
	// �d�͂�������
	Vector3 speed = robot.GetSpeed();
	speed.y += Object3D::GRAVITY;
	robot.SetSpeed(speed);
}

/// <summary>
/// �o������
/// </summary>
/// <param name="robot"></param>
void JumpingState::Exit(Robot & robot)
{
}
