#pragma once

#include "Robot.h"

class PlayerRobot :public Robot	// ロボットを継承
{
private :
	// 弾の速度
	DirectX::SimpleMath::Vector3 m_BulletVel;

	// 弾丸発射中フラグ
	bool m_FireFlag;

	// 弾の当たり判定球
	SphereNode m_CollisionNode;

public:
	PlayerRobot();			// コンストラクタ	
	virtual ~PlayerRobot();	// デストラクタ

	//　更新
	void Update()override;

	// 描画
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) const override;

	// 発射
	void FireBullet();
	// 弾リセット
	void ResetBullet();

	// 当たり判定球を取得
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNode; }

	// 当たった時の処理
	void OnCollisionEnter(const Object3D& obj) override;
};

