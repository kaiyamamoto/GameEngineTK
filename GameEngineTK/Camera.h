
// Camera クラス

#pragma once
#include <simplemath.h>

class Camera
{
protected:
	DirectX::SimpleMath::Matrix		m_view;		// ビュー行列
	DirectX::SimpleMath::Vector3	m_eyePos;	// カメラの位置
	DirectX::SimpleMath::Vector3	m_refPos;	// 注視点
	DirectX::SimpleMath::Vector3	m_upVec;	// 上方向ベクトル
	DirectX::SimpleMath::Matrix		m_proj;		// 射影行列
	float							m_fovY;		// 垂直方向視野角(縦の視野)
	float							m_aspect;	// 画面の縦横比率
	float							m_nearClip;	// 手前の表示限界
	float							m_farClip;	// 奥の表示限界

public:
	Camera(int screenWidth, int screenHeight);			// コンストラクタ
	virtual ~Camera();							// 仮想デストラクタ

	void Update();		// 更新
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_view; }
	DirectX::SimpleMath::Matrix GetProjMatrix() const { return m_proj; }
	void SetEyePos(const DirectX::SimpleMath::Vector3 &eyePos) { m_eyePos = eyePos; }
	void SetRefPos(const DirectX::SimpleMath::Vector3 &refPos) {m_refPos = refPos;}
	void SetUpVecPos(const DirectX::SimpleMath::Vector3 &upVec) { 
		m_upVec = upVec; 
		m_upVec.Normalize();
	}
};

