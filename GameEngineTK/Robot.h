// 
// BoinRobot�̃N���X
// K.Yamamoto
// 

#pragma once

#include<simplemath.h>
#include "Object3D.h"
#include <vector>
#include <Keyboard.h>
#include "State\\RobotState.h"
#include <math.h>

class RobotState;

class Robot :public Object3D
{
public:	// ��
	enum Parts:long
	{
		BODY = 0,
		HEAD,
		RIGHTARM,
		LEFTARM,
		RIGHTLEG,
		LEFTLEG,
		length
	};
protected:
	std::vector<std::unique_ptr<Object3D>> m_robotParts;	// �p�[�c
	RobotState* m_state;									// �X�e�[�g

	// ���x
	DirectX::SimpleMath::Vector3 m_speed;

	// �����x
	DirectX::SimpleMath::Vector3 m_acceleSpeed;
public:
	Robot();
	virtual ~Robot(){}

	// ������
	void Initialize();

	// �`��
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) const;

	//�@�X�V
	void Update();

	// �s��̌v�Z
	void Calc();

	// ���x�ݒ�
	DirectX::SimpleMath::Vector3 GetSpeed() { return m_speed; }
	void SetSpeed(DirectX::SimpleMath::Vector3 vec) { m_speed = vec; }
	
	// �����x�ݒ�
	void SetAcceleSpeed(DirectX::SimpleMath::Vector3 vec) { m_acceleSpeed = vec; }

	// �p�[�c�擾
	Object3D* GetRobotParts(Parts parts) { return m_robotParts[parts].get(); }
};
