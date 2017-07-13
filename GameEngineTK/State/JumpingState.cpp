#include "JumpingState.h"
#include "OnGroundState.h"
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
	// スタンディング状態の処理
	OnGroundState::GetInstance()->HandleInput(robot);

	float posY = robot.GetPosition().y;

	//// 座標で判定（いずれ地面判定など）
	//if (posY <= 1.0f) {		
	//	// ジャンプ終了
	//	return OnGroundState::GetInstance();
	//}
	return nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void JumpingState::Update(Robot & robot)
{
	// 速度を反映
	Vector3 speed = robot.GetSpeed();
	speed.y += Object3D::GRAVITY;
	robot.SetSpeedY(speed.y);
}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="robot"></param>
void JumpingState::Exit(Robot & robot)
{
	// 速度を戻す
	robot.SetSpeedY(0.0f);
}
