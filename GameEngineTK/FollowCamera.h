
// FollowCamera �N���X

#pragma once
#include <simplemath.h>
#include "Camera.h"
#include "Object3D.h"

class FollowCamera :public Camera
{
private:
	Object3D* m_pObject;					// �Ǐ]����I�u�W�F�N�g

public:
	// �萔 //
	static const float CAMERA_DISTANCE;		// �J�����̋���

	// �R���X�g���N�^
	FollowCamera(Object3D* pObj = nullptr, int screenWidth = 480, int screenHeight = 640);
	// �f�X�g���N�^
	~FollowCamera();

	// �X�V
	void Update() override;

};