// 
// Robotのクラス
// K.Yamamoto
// 

#include "Robot.h"
#include"State\OnGroundState.h"

// 名前空間
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Robot::Robot()
	:Object3D()
	,m_robotParts(Parts::length)
	,m_state(OnGroundState::GetInstance())	// 初期状態後で変更
	,m_speed(Vector3(0.0f,0.0f,0.0f))
	,m_acceleSpeed(Vector3(0.0f,0.05f,0.0f))
{
	// 初期化
	Initialize();
}

// 初期化
void Robot::Initialize()
{
	// オブジェクトの読み込み
	m_robotParts[BODY] = std::make_unique<Object3D>(L"Resources\\body.cmo");
	m_robotParts[HEAD] = std::make_unique<Object3D>(L"Resources\\head.cmo");
	m_robotParts[RIGHTARM] = std::make_unique<Object3D>(L"Resources\\missile.cmo");
	m_robotParts[LEFTARM] = std::make_unique<Object3D>(L"Resources\\missile.cmo");
	m_robotParts[RIGHTLEG] = std::make_unique<Object3D>(L"Resources\\leg.cmo");
	m_robotParts[LEFTLEG] = std::make_unique<Object3D>(L"Resources\\leg.cmo");

	// 親子関係
	// 全パーツBODYの子になる
	m_robotParts[BODY]->SetParent(this);
	m_robotParts[HEAD]->SetParent(m_robotParts[BODY].get());
	m_robotParts[RIGHTARM]->SetParent(m_robotParts[BODY].get());
	m_robotParts[LEFTARM]->SetParent(m_robotParts[BODY].get());
	m_robotParts[RIGHTLEG]->SetParent(m_robotParts[BODY].get());
	m_robotParts[LEFTLEG]->SetParent(m_robotParts[BODY].get());

	// サイズ設定
	this->SetScale(0.5f);

	// 全体的な座標調整
	m_robotParts[HEAD]->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
	m_robotParts[RIGHTARM]->SetPosition(Vector3(2.0f, 2.0f, 0.0f));
	m_robotParts[LEFTARM]->SetPosition(Vector3(-2.0f, 2.0f, 0.0f));
	m_robotParts[RIGHTLEG]->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
	m_robotParts[LEFTLEG]->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
}

/// <summary>
/// 描画
/// </summary>
/// <param name="state"></param>
/// <param name="view"></param>
/// <param name="proj"></param>
void Robot::Draw(const DirectX::CommonStates & state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	for (auto itr = m_robotParts.begin(); itr != m_robotParts.end(); ++itr) {
		(*itr)->Draw(state, view, proj);
	}
}

/// <summary>
/// 更新
/// </summary>
void Robot::Update()
{
	// 基底の更新
	this->Object3D::Update();
	// モデルの行列更新
	Calc();

	// 移動
	m_position += m_speed;
}

/// <summary>
/// 行列の更新
/// </summary>
void Robot::Calc()
{
	for (auto itr = m_robotParts.begin(); itr != m_robotParts.end(); ++itr)
	{
		(*itr)->Update();
	}
}