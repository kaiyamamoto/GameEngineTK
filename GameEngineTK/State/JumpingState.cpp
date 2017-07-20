#include "JumpingState.h"
#include "OnGroundState.h"
#include "MoveState.h"
#include "InAirState.h"
#include <simplemath.h>

using namespace DirectX::SimpleMath;

JumpingState* JumpingState::m_instance = nullptr;

/// <summary>
/// 入口処理
/// </summary>
/// <param name="player"></param>
void JumpingState::Enter(Robot & robot)
{
	// Y軸に速度設定
	robot.SetSpeedY(0.5f);
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keyTracker">入力されたキー</param>
/// <returns>次の状態があるときは状態を返す</returns>
RobotState * JumpingState::HandleInput(Robot & robot)
{
	return InAirState::GetInstance();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void JumpingState::Update(Robot & robot)
{
}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="robot"></param>
void JumpingState::Exit(Robot & robot)
{
}
