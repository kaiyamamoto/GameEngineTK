#include "PlayerRobot.h"
#include "State\StandingState.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerRobot::PlayerRobot()
	:Robot()
{
	// 立っている状態
	m_state = StandingState::GetInstance();
	m_state->Enter(*this);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerRobot::~PlayerRobot()
{
}

/// <summary>
/// 更新
/// </summary>
void PlayerRobot::Update()
{
	// 更新
	m_state->Update(*this);

	RobotState* localstate = m_state->HandleInput(*this);
	if (localstate != nullptr) {
		m_state->Exit(*this);
		m_state = localstate;
		// 入口処理
		m_state->Enter(*this);
	}
	// ロボットの更新
	this->Robot::Update();
}


