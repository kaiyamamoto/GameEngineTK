#pragma once
#include "RobotState.h"

class InAirState :
	public RobotState
{
private:
	InAirState(){}
	static InAirState* m_instance;
public:
	// ƒVƒ“ƒOƒ‹ƒgƒ“
	static InAirState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new InAirState();
		}
		return m_instance;
	}

	void Enter(Robot& robot)override;
	RobotState* HandleInput(Robot& robot)override;
	void Update(Robot& robot) override;
	void Exit(Robot& robot) override;
};