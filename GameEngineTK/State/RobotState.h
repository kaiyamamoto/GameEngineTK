#pragma once

#include "../Robot.h"
#include <typeinfo.h>  

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

	const wchar_t* GetStateName() {
		// å^èÓïÒÇÃéÊìæ  
		const type_info& id = typeid(*this);
		const char* name = id.name();
		size_t newsize = strlen(name) + 1;
		wchar_t * wcstring = new wchar_t[newsize];
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wcstring, newsize, name, _TRUNCATE);
		return &*wcstring;
	}
};

