/// <summary>
/// �����蔻��m�[�h
/// </summary>
#pragma once

#include <simplemath.h>
#include "Object3D.h"
#include "Collision.h"

// �����蔻��m�[�h�Ǘ��N���X
class CollisionNode
{
public:
	enum TYPE
	{
		TYPE_SPHERE,	// ��
		TYPE_CAPSULE,	// �J�v�Z��

		TYPE_NUM
	};
private:
	// �f�o�b�O�\����ON/OFF�t���O
	static bool s_DebugVisible;
public:
	// �f�o�b�O�\����ON/OFF��ݒ�
	static void SetDebugVisible(bool flag) { s_DebugVisible = flag; }
	// �f�o�b�O�\����ON/OFF���擾
	static bool GetDebugVisible(void) { return s_DebugVisible; }

protected:
	// �\���p�I�u�W�F�N�g
	Object3D m_Obj;
public:
	virtual void Initialize() = 0;
	// �`��
	virtual void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)const = 0;
	// �X�V
	virtual void Update() = 0;

	// �e��ݒ�
	void SetParent(Object3D* pParent);

	// �����蔻��֐��@==========================================
	// �����Ɩ@���t���O�p�`
	static bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter = nullptr);

	static void ClosestPtPoint2Triangle(const DirectX::SimpleMath::Vector3 & _point, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _closest);

	// �_�Ɩ@���t���O�p�`
	static bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3 & _point, const Triangle & _triangle);

	//���Ɩ@���t���O�p�`
	static bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter = nullptr); 

	// ���Ƌ�
	static bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
};

// �����蔻�苅�m�[�h
class SphereNode : public CollisionNode, public Sphere
{
public:
	// �R���X�g���N�^
	SphereNode();
	// ������
	void Initialize();
	// �`��
	virtual void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)const override;
	// �X�V
	void Update();
	// ���[�J�����a��ݒ�
	void SetLocalRadius(float radius) { m_LocalRadius = radius; }
	// �e�s�񂩂�̃I�t�Z�b�g��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
protected:
	// �e�s��̉e�����󂯂�O�̃��[�J�����a
	float m_LocalRadius;
	// �e�s�񂩂�̃I�t�Z�b�g���W
	DirectX::SimpleMath::Vector3 m_Trans;
};