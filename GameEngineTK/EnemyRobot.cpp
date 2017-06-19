#include "Input.h"
#include "EnemyRobot.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyRobot::EnemyRobot()
	:Robot()
{
	// 初期化
	this->Robot::Initialize();

	// 初期座標をランダムに決定
	Vector3 pos;

	pos.x = static_cast<float>(rand() % 10);
	pos.z = static_cast<float>(rand() % 10);

	SetPosition(pos);

	m_Timer = 0;
	m_DistAngle = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyRobot::~EnemyRobot()
{
}

/// <summary>
/// 更新
/// </summary>
void EnemyRobot::Update()
{
	m_Timer--;
	if (m_Timer < 0)
	{
		// 目標角度の再抽選
		m_Timer = 60;
		// -0.5〜+0.5の乱数
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		// -90〜+90の乱数
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// 自機の角度を変動
		Vector3 rot = this->GetRotateRadians();

		float angle = m_DistAngle - rot.y;

		if (angle > XM_PI)	angle -= XM_2PI;
		if (angle < -XM_PI)	angle += XM_2PI;

		rot.y += angle *0.05f;

		SetRotateRadians(rot);

	}

	// 機体の向いている方向に前進
	{
		// 移動ベクトル
		Vector3 moveV(0, 0, -0.1f);
		// 今の角度に合わせて移動ベクトルを回転
		// 回転行列
		float angle = this->GetRotateRadians().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動
		Vector3 pos = this->GetPosition();
		pos += moveV;
		this->SetPosition(pos);
	}

	// ロボットの行列更新
	this->Robot::Update();
}
