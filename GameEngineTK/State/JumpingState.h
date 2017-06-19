#pragma once
#include "RobotState.h"

class JumpingState :
	public RobotState
{
private:
	JumpingState() {}
	static JumpingState* m_instance;

public:
	~JumpingState() {};

	// ƒVƒ“ƒOƒ‹ƒgƒ“
	static JumpingState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new JumpingState();
		}
		return m_instance;
	}

	void Enter(Robot& robot)override;
	RobotState* HandleInput(Robot& robot)override;
	void Update(Robot& robot) override;
	void Exit(Robot& robot) override;
};

