#include "RobotCommonState.h"
#include <simplemath.h>
#include "..\Input.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace YamagenLib;

RobotCommonState* RobotCommonState::m_instance = nullptr;

/// <summary>
/// 入口処理
/// </summary>
/// <param name="player"></param>
void RobotCommonState::Enter(Robot & player)
{
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keyTracker">入力されたキー</param>
/// <returns>次の状態があるときは状態を返す</returns>
RobotState * RobotCommonState::HandleInput(Robot & robot)
{
	// ロボ回転
	Vector3 roteV = Vector3(0.0f, 0.0f, 0.0f);
	float rotY = 0.01f;
	if (robot.GetSpeed().z == 0.0f) {
		rotY = 0.001f;
	}
	if (Input::GetKey(Key::D))	roteV = Vector3(0.0f, -rotY, 0.0f);
	else if (Input::GetKey(Key::A)) roteV = Vector3(0.0f, rotY, 0.0f);
	robot.SetEulerAngle(robot.GetEulerAngle() + roteV);

	return nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void RobotCommonState::Update(Robot & robot)
{
}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="robot"></param>
void RobotCommonState::Exit(Robot & robot)
{
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

