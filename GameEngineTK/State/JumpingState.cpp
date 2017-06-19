#include "JumpingState.h"
#include "StandingState.h"
#include <simplemath.h>

using namespace DirectX::SimpleMath;

JumpingState* JumpingState::m_instance = nullptr;

/// <summary>
/// 入口処理
/// </summary>
/// <param name="player"></param>
void JumpingState::Enter(Robot & robot)
{
	Vector3 speed = robot.GetSpeed();
	speed.y += 0.5f;
	robot.SetSpeed(speed);
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keyTracker">入力されたキー</param>
/// <returns>次の状態があるときは状態を返す</returns>
RobotState * JumpingState::HandleInput(Robot & robot)
{
	// スタンディング状態の処理
	StandingState::GetInstance()->HandleInput(robot);

	Vector3 pos = robot.GetPosition();

	if (pos.y <= 1.0f) {		
		Vector3 speed = robot.GetSpeed();
		speed.y = 0.0f;
		robot.SetSpeed(speed);
		// ジャンプ終了
		return StandingState::GetInstance();
	}
	return nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void JumpingState::Update(Robot & robot)
{
	// 重力を加える
	Vector3 speed = robot.GetSpeed();
	speed.y += Object3D::GRAVITY;
	robot.SetSpeed(speed);
}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="robot"></param>
void JumpingState::Exit(Robot & robot)
{
}
