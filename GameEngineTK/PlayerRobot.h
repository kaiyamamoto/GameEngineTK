#pragma once

#include "Robot.h"

class PlayerRobot :public Robot	// ロボットを継承
{
public:
	PlayerRobot();			// コンストラクタ	
	virtual ~PlayerRobot();	// デストラクタ

	//　更新
	void Update();
};

