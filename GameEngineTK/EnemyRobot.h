#pragma once

#include "Robot.h"

class EnemyRobot :public Robot	// ���{�b�g���p��
{
public:
	EnemyRobot();			// �R���X�g���N�^	
	virtual ~EnemyRobot();	// �f�X�g���N�^

	//�@�X�V
	void Update();

	// ���@�̃M�~�b�N�Ɏg���p�x
	float m_sinAngle;
	// �^�C�}�[
	int m_Timer;
	// �ڕW�p�x
	float m_DistAngle;
};

