#pragma once
#include "RobotState.h"

class RobotCommonState :
	public RobotState
{
private:
	RobotCommonState(){}
	static RobotCommonState* m_instance;

public:
	// ƒVƒ“ƒOƒ‹ƒgƒ“
	static RobotCommonState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new RobotCommonState();
		}
		return m_instance;
	}

	void Enter(Robot& robot)override;
	RobotState* HandleInput(Robot& robot)override;
	void Update(Robot& robot) override;
	void Exit(Robot& robot) override;
};