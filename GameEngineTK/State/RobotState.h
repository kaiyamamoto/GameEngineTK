#pragma once

#include "../Robot.h"

using Microsoft::WRL::ComPtr;
class Robot;

class RobotState
{
protected:
public:
	RobotState() {}
	virtual ~RobotState() {}

	virtual void Enter(Robot& robot) = 0;
	virtual RobotState* HandleInput(Robot& robot) = 0;
	virtual void Update(Robot& robot) = 0;
	virtual void Exit(Robot& robot) = 0;
};

