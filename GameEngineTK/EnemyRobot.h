#pragma once

#include "Robot.h"

class EnemyRobot :public Robot	// ロボットを継承
{
public:
	EnemyRobot();			// コンストラクタ	
	virtual ~EnemyRobot();	// デストラクタ

	//　更新
	void Update();

	// 自機のギミックに使う角度
	float m_sinAngle;
	// タイマー
	int m_Timer;
	// 目標角度
	float m_DistAngle;
};

