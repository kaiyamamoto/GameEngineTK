#include "InAirState.h"
#include "JumpingState.h"
#include "MoveState.h"
#include <simplemath.h>
#include "..\Input.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace YamagenLib;

InAirState* InAirState::m_instance = nullptr;

/// <summary>
/// 入口処理
/// </summary>
/// <param name="player"></param>
void InAirState::Enter(Robot & player)
{
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keyTracker">入力されたキー</param>
/// <returns>次の状態があるときは状態を返す</returns>
RobotState * InAirState::HandleInput(Robot & robot)
{
	MoveState::GetInstance()->HandleInput(robot);

	// ジャンプ
	if (Input::GetKeyDown(Key::Space)) 		return JumpingState::GetInstance();

	return nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void InAirState::Update(Robot & robot)
{
	// 重力を反映
	//m_speed.y += Object3D::GRAVITY;
	float speedY = robot.GetSpeed().y;
	speedY += Object3D::GRAVITY;
	robot.SetSpeedY(speedY);

}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="robot"></param>
void InAirState::Exit(Robot & robot)
{
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

