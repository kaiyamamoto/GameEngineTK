/// <summary>
/// 当たり判定ノード
/// </summary>
#pragma once

#include <simplemath.h>
#include "Object3D.h"
#include "Collision.h"

// 当たり判定ノード管理クラス
class CollisionNode
{
public:
	enum TYPE
	{
		TYPE_SPHERE,	// 球
		TYPE_CAPSULE,	// カプセル

		TYPE_NUM
	};
private:
	// デバッグ表示のON/OFFフラグ
	static bool s_DebugVisible;
public:
	// デバッグ表示のON/OFFを設定
	static void SetDebugVisible(bool flag) { s_DebugVisible = flag; }
	// デバッグ表示のON/OFFを取得
	static bool GetDebugVisible(void) { return s_DebugVisible; }

protected:
	// 表示用オブジェクト
	Object3D m_Obj;
public:
	virtual void Initialize() = 0;
	// 描画
	virtual void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)const = 0;
	// 更新
	virtual void Update() = 0;

	// 親を設定
	void SetParent(Object3D* pParent);

	// あたり判定関数　==========================================
	// 線分と法線付き三角形
	static bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter = nullptr);

	static void ClosestPtPoint2Triangle(const DirectX::SimpleMath::Vector3 & _point, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _closest);

	// 点と法線付き三角形
	static bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3 & _point, const Triangle & _triangle);

	//球と法線付き三角形
	static bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter = nullptr); 

	// 球と球
	static bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
};

// 当たり判定球ノード
class SphereNode : public CollisionNode, public Sphere
{
public:
	// コンストラクタ
	SphereNode();
	// 初期化
	void Initialize();
	// 描画
	virtual void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)const override;
	// 更新
	void Update();
	// ローカル半径を設定
	void SetLocalRadius(float radius) { m_LocalRadius = radius; }
	// 親行列からのオフセットを設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
protected:
	// 親行列の影響を受ける前のローカル半径
	float m_LocalRadius;
	// 親行列からのオフセット座標
	DirectX::SimpleMath::Vector3 m_Trans;
};