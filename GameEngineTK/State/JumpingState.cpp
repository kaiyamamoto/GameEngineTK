#include "JumpingState.h"
#include "OnGroundState.h"
#include "MoveState.h"
#include "InAirState.h"
#include <simplemath.h>

using namespace DirectX::SimpleMath;

JumpingState* JumpingState::m_instance = nullptr;

/// <summary>
/// ��������
/// </summary>
/// <param name="player"></param>
void JumpingState::Enter(Robot & robot)
{
	// Y���ɑ��x�ݒ�
	robot.SetSpeedY(0.5f);
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="keyTracker">���͂��ꂽ�L�[</param>
/// <returns>���̏�Ԃ�����Ƃ��͏�Ԃ�Ԃ�</returns>
RobotState * JumpingState::HandleInput(Robot & robot)
{
	return InAirState::GetInstance();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player"></param>
void JumpingState::Update(Robot & robot)
{
}

/// <summary>
/// �o������
/// </summary>
/// <param name="robot"></param>
void JumpingState::Exit(Robot & robot)
{
}
