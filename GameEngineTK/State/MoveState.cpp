#include "MoveState.h"
#include "JumpingState.h"
#include "OnGroundState.h"
#include <simplemath.h>
#include "..\Input.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace YamagenLib;

MoveState* MoveState::m_instance = nullptr;

/// <summary>
/// 入口処理
/// </summary>
/// <param name="player"></param>
void MoveState::Enter(Robot & player)
{
	m_time = 0.0f;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keyTracker">入力されたキー</param>
/// <returns>次の状態があるときは状態を返す</returns>
RobotState * MoveState::HandleInput(Robot & robot)
{
	// ジャンプ
	if (Input::GetKeyDown(Key::Space)) 		return JumpingState::GetInstance();

	// ロボ移動
	if (Input::GetKey(Key::W))		 robot.SetSpeedZ(-0.3f);
	else if (Input::GetKey(Key::S)) robot.SetSpeedZ(0.3f);
	// 移動していなかったら戻る
	else {
		robot.SetSpeedZ(0.0f);
		return OnGroundState::GetInstance();
	}
	// アニメーション用
	if (robot.GetSpeed().z != 0.0f) m_isWalke = true;
	else m_isWalke = false;

	return nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void MoveState::Update(Robot & robot)
{
	m_time += 0.016;
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Lerp(Vector3(1.0f, 0.0f, 1.0f), Vector3(1.0f, 0.0f, -1.0f), m_time));
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Lerp(Vector3(-1.0f, 0.0f, -1.0f), Vector3(-1.0f, 0.0f, 1.0f), m_time));

	if (m_time == 2.0f) {
		m_time = 0.0f;
	}
}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="robot"></param>
void MoveState::Exit(Robot & robot)
{
	// 移動終了
	robot.SetSpeedZ(0.0f);
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

