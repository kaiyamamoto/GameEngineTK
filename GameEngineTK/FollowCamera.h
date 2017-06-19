
// FollowCamera クラス

#pragma once
#include <simplemath.h>
#include "Camera.h"
#include "Object3D.h"

class FollowCamera :public Camera
{
private:
	Object3D* m_pObject;					// 追従するオブジェクト

public:
	// 定数 //
	static const float CAMERA_DISTANCE;		// カメラの距離

	// コンストラクタ
	FollowCamera(Object3D* pObj = nullptr, int screenWidth = 480, int screenHeight = 640);
	// デストラクタ
	~FollowCamera();

	// 更新
	void Update() override;

};