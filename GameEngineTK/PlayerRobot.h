#pragma once

#include "Robot.h"

class PlayerRobot :public Robot	// ���{�b�g���p��
{
public:
	PlayerRobot();			// �R���X�g���N�^	
	virtual ~PlayerRobot();	// �f�X�g���N�^

	//�@�X�V
	void Update();
};

