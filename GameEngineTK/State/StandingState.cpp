#include "StandingState.h"
#include "JumpingState.h"
#include <simplemath.h>
#include "..\Input.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace YamagenLib;

StandingState* StandingState::m_instance = nullptr;

/// <summary>
/// 入口処理
/// </summary>
/// <param name="player"></param>
void StandingState::Enter(Robot & player)
{
	m_time = 0.0f;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keyTracker">入力されたキー</param>
/// <returns>次の状態があるときは状態を返す</returns>
RobotState * StandingState::HandleInput(Robot & robot)
{
	Update(robot);

	// ロボ回転	関数化
	Vector3 roteV = Vector3(0.0f, 0.0f, 0.0f);
	if		(Input::GetKey(Input::Key::D))	  roteV = Vector3(0.0f, -0.01f, 0.0f);
	else if (Input::GetKey(Input::Key::A)) roteV = Vector3(0.0f, 0.01f, 0.0f);
	robot.SetRotate(robot.GetRotate() + roteV);

	// ロボ移動	関数化
	Vector3 moveV = Vector3(0.0f, 0.0f, 0.0f);
	if		(Input::GetKey(Input::Key::W))		 moveV = Vector3(0.0f, 0.0f, -0.1f);

	else if (Input::GetKey(Input::Key::S)) moveV = Vector3(0.0f, 0.0f, +0.1f);

	if (moveV != Vector3::Zero) m_isWalke = true;
	else m_isWalke = false;

	// 移動回転	関数化
	Matrix rotmat = Matrix::Identity;
	rotmat *= Matrix::CreateRotationY(robot.GetRotateRadians().y);
	moveV = Vector3::TransformNormal(moveV, rotmat);
	robot.SetPosition(robot.GetPosition() + moveV);

	if (Input::GetKeyDown(Input::Key::Space)) {
		// 地面にいるならジャンプ
		return JumpingState::GetInstance();
	}

	return nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void StandingState::Update(Robot & robot)
{
	if (m_isWalke)
	{
		m_time += 0.016;
		robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Lerp(Vector3(1.0f, 0.0f, 1.0f), Vector3(1.0f, 0.0f, -1.0f), m_time));
		robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Lerp(Vector3(-1.0f, 0.0f, -1.0f), Vector3(-1.0f, 0.0f, 1.0f), m_time));
	}

	if (m_time == 2.0f) {
		m_time = 0.0f;
	}
}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="robot"></param>
void StandingState::Exit(Robot & robot)
{
	robot.GetRobotParts(Robot::Parts::LEFTLEG)->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	robot.GetRobotParts(Robot::Parts::RIGHTLEG)->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

