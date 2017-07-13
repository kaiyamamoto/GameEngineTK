#include "pch.h"
#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float FollowCamera::CAMERA_DISTANCE = 10.0f;		// カメラの距離

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pObj">追従するオブジェクト</param>
/// <param name="screenWidth">画面の幅</param>
/// <param name="screenHeight">画面の高さ</param>
/// <param name="distance=5.0f">カメラとの距離</param>
FollowCamera::FollowCamera(Object3D* pObj, int screenWidth, int screenHeight)
	:m_pObject(pObj)
	, Camera(screenWidth, screenHeight)
{
}

/// <summary>
/// デストラクタ
/// </summary>
FollowCamera::~FollowCamera()
{

}

/// <summary>
/// 更新
/// </summary>
void FollowCamera::Update()
{
	// 視点、参照点
	Vector3 eyepos, refpos;

	//Vector3 objUpPos;

	//// カメラ座標計算
	//objUpPos = m_pObject->GetPosition() + Vector3(0.0f, 0.2f, 0.0f);

	//// カメラ座標への差分
	//Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);

	//// カメラの視点方向の逆方向に回転
	//Matrix rotmat = Matrix::CreateRotationY(m_pObject->GetRotateRadians().y);
	//cameraV = Vector3::TransformNormal(cameraV, rotmat);
	//
	//// 雑
	//eyepos = objUpPos + cameraV * 0.05f;
	//// 参照点を計算
	//refpos = eyepos + cameraV;

	// オブジェクトを追従
	refpos = m_pObject->GetPosition() + Vector3(0.0f, 2.0f, 0.0f);
	// カメラ座標への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);

	// カメラの視点方向の逆方向に回転
	Matrix rotmat = Matrix::CreateRotationY(m_pObject->GetEulerAngleRadians().y);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	// カメラ座標計算
	eyepos = refpos + cameraV;

	// ゴム紐用 ==================================
	// 視点を現在位置から補間
	eyepos = m_eyePos + (eyepos - m_eyePos)*0.05f;
	// 参照点を現在位置から補間
	refpos = m_refPos + (refpos - m_refPos)*0.2f;
	// ===========================================

	// カメラの更新
	SetEyePos(eyepos);	// カメラ位置
	SetRefPos(refpos);	// 参照点
	SetUpVecPos(Vector3(0, 1, 0));		// 上方向ベクトル

	// 基底クラスのカメラの更新
	this->Camera::Update();
}
