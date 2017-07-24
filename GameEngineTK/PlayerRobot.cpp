#include "PlayerRobot.h"
#include "State\OnGroundState.h"
#include "State\RobotCommonState.h"
#include "Input.h"
#include "Stage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace YamagenLib;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerRobot::PlayerRobot()
	:Robot()
	, m_FireFlag(false)
{
	// 立っている状態
	m_state = OnGroundState::GetInstance();
	m_state->Enter(*this);

	m_CollisionNodeBody.Initialize();
	// ベースパーツにぶら下げる
	m_CollisionNodeBody.SetParent(this);
	// ベースパーツからのオフセット
	m_CollisionNodeBody.SetTrans(Vector3(0, 1.0f, 0));
	// 当たり判定の半径
	m_CollisionNodeBody.SetLocalRadius(2.0f);

	m_CollisionNode.Initialize();
	// 自機に着ける
	m_CollisionNode.SetParent(m_robotParts[Parts::RIGHTARM].get());
	// 武器パーツからのオフセット
	m_CollisionNode.SetTrans(Vector3(0, 0.0f, -1.5f));
	// 当たり判定の半径
	m_CollisionNode.SetLocalRadius(1.0f);
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
	// 共通処理
	RobotCommonState::GetInstance()->HandleInput(*this);
	// 遷移処理
	// 入力周り
	RobotState* collisionState = this->Robot::CollisionCheck();
	RobotState* localstate = m_state->HandleInput(*this);
	
	if (collisionState) localstate = collisionState;

	// あたり判定周り
	if (localstate != nullptr) {
		m_state->Exit(*this);
		m_state = localstate;
		// 入口処理
		m_state->Enter(*this);
	}
	// 状態の更新
	m_state->Update(*this);

	// 弾
	if (Input::GetKeyDown(Key::RightShift)) FireBullet();

	// ロボットの更新
	this->Robot::Update();

	// あたり判定更新
	// あたり判定の更新
	m_CollisionNodeBody.Update();
	m_CollisionNode.Update();

	// 弾丸が進む処理
	if (m_FireFlag)
	{
		// 自機の座標を移動
		Vector3 pos = m_robotParts[Parts::RIGHTARM]->GetPosition();
		pos += m_BulletVel;
		m_robotParts[Parts::RIGHTARM]->SetPosition(pos);
	}
}

/// <summary>
/// 　描画
/// </summary>
/// <param name="state">ステート</param>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void PlayerRobot::Draw(const DirectX::CommonStates & state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	// 基底の描画
	this->Robot::Draw(state, view, proj);

	m_CollisionNode.Draw(state, view, proj);
	m_CollisionNodeBody.Draw(state, view, proj);
	// デバッグ

	// stateの表示
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), m_state->GetStateName(), XMFLOAT2(0.0f, 0.0f));
	spriteBatch->End();
}

/// <summary>
/// 発射
/// </summary>
void PlayerRobot::FireBullet()
{
	if (m_FireFlag)
	{
		ResetBullet();
		return;
	}

	// ワールド行列を取得
	Matrix worldm = m_robotParts[Parts::RIGHTARM]->GetWorld();

	Vector3 scale;	// ワールドスケーリング
	Quaternion rotation;	// ワールド回転
	Vector3 translation;	// ワールド座標

							// ワールド行列から各要素を取り出す
	worldm.Decompose(scale, rotation, translation);

	// 親子関係を解除してパーツを独立させる
	m_robotParts[Parts::RIGHTARM]->SetParent(nullptr);
	m_robotParts[Parts::RIGHTARM]->SetScale(scale);
	m_robotParts[Parts::RIGHTARM]->SetRotation(rotation);
	m_robotParts[Parts::RIGHTARM]->SetPosition(translation);

	// 弾の速度を設定
	m_BulletVel = Vector3(0, 0, -0.5f);
	// 弾の向きに合わせて進行方向を回転
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_FireFlag = true;
}

/// <summary>
/// 弾リセット
/// </summary>
void PlayerRobot::ResetBullet()
{
	m_robotParts[Parts::RIGHTARM]->SetParent(
		m_robotParts[Parts::BODY].get());

	m_robotParts[Parts::RIGHTARM]->SetPosition(
		Vector3(2.0f, 2.0f, 0.0f));
	m_robotParts[Parts::RIGHTARM]->SetScale(1.0f);
	m_robotParts[Parts::RIGHTARM]->SetEulerAngleRadians(Vector3(0, 0, 0));

	m_FireFlag = false;
}

/// <summary>
/// 当たった時の処理
/// </summary>
/// <param name="tag">当たったオブジェクトの種類</param>
void PlayerRobot::OnCollisionEnter(const Object3D& obj)
{
	// 型情報の取得  
	const type_info& id = typeid(obj);

	// 当たったのがステージの時
	if (id == typeid(LandShape)) {
		// 上に居るとき
		if (m_position.y > obj.GetPosition().y) {
			// 地面の上にいる状態になる
			m_state = OnGroundState::GetInstance();
		}
	}
}
