#include "JumpingState.h"
#include "OnGroundState.h"
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
	// �X�^���f�B���O��Ԃ̏���
	OnGroundState::GetInstance()->HandleInput(robot);

	float posY = robot.GetPosition().y;

	//// ���W�Ŕ���i������n�ʔ���Ȃǁj
	//if (posY <= 1.0f) {		
	//	// �W�����v�I��
	//	return OnGroundState::GetInstance();
	//}
	return nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player"></param>
void JumpingState::Update(Robot & robot)
{
	// ���x�𔽉f
	Vector3 speed = robot.GetSpeed();
	speed.y += Object3D::GRAVITY;
	robot.SetSpeedY(speed.y);
}

/// <summary>
/// �o������
/// </summary>
/// <param name="robot"></param>
void JumpingState::Exit(Robot & robot)
{
	// ���x��߂�
	robot.SetSpeedY(0.0f);
}
