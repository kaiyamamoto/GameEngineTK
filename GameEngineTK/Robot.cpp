// 
// Robotのクラス
// K.Yamamoto
// 

#include "Robot.h"
#include"State\OnGroundState.h"
#include "State\JumpingState.h"
#include "State\InAirState.h"

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
	, m_autoRun(false)
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
	// パーツの描画
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

	// 回転移動
	Vector3 move = m_speed;
	Matrix rotmat = Matrix::Identity;
	rotmat *= Matrix::CreateRotationY(GetEulerAngleRadians().y);
	move = Vector3::TransformNormal(move, rotmat);
	m_position += move;

	// 行列更新
	Calc();
}

/// <summary>
/// 行列の更新
/// </summary>
void Robot::Calc()
{
	// 基底クラスの行列更新
	this->Object3D::Calc();
	// パーツの行列更新
	for (auto itr = m_robotParts.begin(); itr != m_robotParts.end(); ++itr){
		(*itr)->Calc();
	}
}

// あたり判定処理
RobotState * Robot::CollisionCheck()
{
	std::vector<std::shared_ptr<LandShape>> landshape = m_pStage->GetLandshape();
	
	// 水平方向あたり判定
	{
		Sphere sphere = GetCollisionNodeBody();
		Vector3 trans = GetPosition();
		Vector3 sphere2player = trans - sphere.center;

		const int REPEAT_LIMIT = 5;

		int rejectNum = 0;

		for (std::vector<std::shared_ptr<LandShape>>::iterator it = landshape.begin();
			it != landshape.end();
			)
		{
			const LandShape* pLandShape = it->get();

			Vector3 reject;	// 排斥ベクトルを入れるための変数

			if (pLandShape->IntersectSphere(sphere, &reject))
			{
				// めり込み分だけ、球を押し出すように移動
				sphere.center = sphere.center + reject;
				if (++rejectNum >= REPEAT_LIMIT)
				{
					break;
				}
				it = landshape.begin();
			}
			else
			{
				it++;
			}
		}

		SetPositionX(sphere.center.x + sphere2player.x);
		SetPositionZ(sphere.center.z + sphere2player.z);

		Calc();
	}

	// 垂直方向地形あたり判定
	{
		const Vector3& vel = GetSpeed();

		// 速度が上向きでない？
		if (vel.y <= 0.0f)
		{
			bool hit = false;
			Segment player_segment;
			Vector3 player_pos = GetPosition();
			player_segment.start = player_pos + Vector3(0, SEGMENT_LENGTH, 0);
			// 影の位置を検出するため、足元から下方向に余裕をもって判定を取る
			player_segment.end = player_pos + Vector3(0, -SHADOW_DISTANCE, 0);

			// 大きい数字で初期化
			float distance = 1.0e5;
			Vector3 inter;

			for (std::vector<std::shared_ptr<LandShape>>::iterator it = landshape.begin();
				it != landshape.end();
				it++)
			{
				const LandShape* pLandShape = it->get();
				float temp_distance;
				Vector3 temp_inter;

				// 床面との当たりを判定
				if (pLandShape->IntersectSegmentFloor(player_segment, &temp_inter))
				{
					hit = true;
					temp_distance = Vector3::Distance(player_segment.start, temp_inter);
					if (temp_distance < distance)
					{
						inter = temp_inter;
						distance = temp_distance;
					}
					// ループ抜ける
					goto BREAK;
				}
			}
		BREAK:

			bool landing = false;

			// ヒット
			if (hit)
			{
				// 吸着距離の範囲内か？
				if (distance <= SEGMENT_LENGTH + ADSORP_LENGTH)
				{
					// 着地
					landing = true;
					Vector3 new_position = player_pos;
					// めりこむから上げる
					inter.y += 1.0f;
					new_position.y = inter.y;
					SetPositionY(new_position.y);
					// 地面に着く
					return OnGroundState::GetInstance();
				}
			}

			// 着地でなければ
			if (!landing && !hit)
			{// 落下開始
				if ((m_state != InAirState::GetInstance()))
					return InAirState::GetInstance();
			}
			Calc();
		}
	}

	return nullptr;
}
