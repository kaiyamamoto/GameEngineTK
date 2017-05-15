#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary> コンストラクタ </summary>
Camera::Camera(int screenWidth, int screenHeight)
	: m_view(Matrix::Identity)								// ビュー行列
	, m_eyePos(Vector3(0.0f, 0.0f, 0.0f))					// カメラの位置
	, m_refPos(Vector3(0.0f, 0.0f, 0.0f))					// 注視点
	, m_upVec(Vector3(0.0f, 1.0f, 0.0f))					// 上方向ベクトル
	, m_proj(Matrix::Identity)								// 射影行列
	, m_fovY(XMConvertToRadians(60.0f))						// 垂直方向視野角(縦の視野)
	, m_aspect(float(screenWidth) / float(screenHeight))	// 画面の縦横比率
	, m_nearClip(0.1f)										// 手前の表示限界
	, m_farClip(1000.0f)									// 奥の表示限界
{
	m_upVec.Normalize();
}

/// <summary> デストラクタ </summary>
Camera::~Camera()
{
}

/// <summary> 更新 </summary>
void Camera::Update()
{
	// ビュー行列を算出する
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);

}
