#pragma once

#include "Robot.h"

class PlayerRobot :public Robot	// ���{�b�g���p��
{
private :
	// �e�̑��x
	DirectX::SimpleMath::Vector3 m_BulletVel;

	// �e�۔��˒��t���O
	bool m_FireFlag;

	// �e�̓����蔻�苅
	SphereNode m_CollisionNode;

public:
	PlayerRobot();			// �R���X�g���N�^	
	virtual ~PlayerRobot();	// �f�X�g���N�^

	//�@�X�V
	void Update()override;

	// �`��
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) const override;

	// ����
	void FireBullet();
	// �e���Z�b�g
	void ResetBullet();

	// �����蔻�苅���擾
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNode; }

	// �����������̏���
	void OnCollisionEnter(const Object3D& obj) override;
};

