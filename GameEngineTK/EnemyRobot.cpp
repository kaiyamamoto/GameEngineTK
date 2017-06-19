#include "Input.h"
#include "EnemyRobot.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyRobot::EnemyRobot()
	:Robot()
{
	// ������
	this->Robot::Initialize();

	// �������W�������_���Ɍ���
	Vector3 pos;

	pos.x = static_cast<float>(rand() % 10);
	pos.z = static_cast<float>(rand() % 10);

	SetPosition(pos);

	m_Timer = 0;
	m_DistAngle = 0;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyRobot::~EnemyRobot()
{
}

/// <summary>
/// �X�V
/// </summary>
void EnemyRobot::Update()
{
	m_Timer--;
	if (m_Timer < 0)
	{
		// �ڕW�p�x�̍Ē��I
		m_Timer = 60;
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		// -90�`+90�̗���
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// ���@�̊p�x��ϓ�
		Vector3 rot = this->GetRotateRadians();

		float angle = m_DistAngle - rot.y;

		if (angle > XM_PI)	angle -= XM_2PI;
		if (angle < -XM_PI)	angle += XM_2PI;

		rot.y += angle *0.05f;

		SetRotateRadians(rot);

	}

	// �@�̂̌����Ă�������ɑO�i
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		// ��]�s��
		float angle = this->GetRotateRadians().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = this->GetPosition();
		pos += moveV;
		this->SetPosition(pos);
	}

	// ���{�b�g�̍s��X�V
	this->Robot::Update();
}
