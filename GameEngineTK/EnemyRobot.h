#pragma once

#include "Robot.h"

class EnemyRobot :public Robot	// ロボットを継承
{
public:
	EnemyRobot();			// コンストラクタ	
	virtual ~EnemyRobot();	// デストラクタ

	//　更新
	void Update() override;

	// 描画
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) const override;
	
	// 自機のギミックに使う角度
	float m_sinAngle;
	// タイマー
	int m_Timer;
	// 目標角度
	float m_DistAngle;
};

