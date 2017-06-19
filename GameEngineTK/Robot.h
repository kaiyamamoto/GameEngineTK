// 
// BoinRobotのクラス
// K.Yamamoto
// 

#pragma once

#include<simplemath.h>
#include "Object3D.h"
#include <vector>
#include <Keyboard.h>
#include "State\\RobotState.h"
#include <math.h>

class RobotState;

class Robot :public Object3D
{
public:	// 列挙
	enum Parts:long
	{
		BODY = 0,
		HEAD,
		RIGHTARM,
		LEFTARM,
		RIGHTLEG,
		LEFTLEG,
		length
	};
protected:
	std::vector<std::unique_ptr<Object3D>> m_robotParts;	// パーツ
	RobotState* m_state;									// ステート

	// 速度
	DirectX::SimpleMath::Vector3 m_speed;

	// 加速度
	DirectX::SimpleMath::Vector3 m_acceleSpeed;
public:
	Robot();
	virtual ~Robot(){}

	// 初期化
	void Initialize();

	// 描画
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) const;

	//　更新
	void Update();

	// 行列の計算
	void Calc();

	// 速度設定
	DirectX::SimpleMath::Vector3 GetSpeed() { return m_speed; }
	void SetSpeed(DirectX::SimpleMath::Vector3 vec) { m_speed = vec; }
	
	// 加速度設定
	void SetAcceleSpeed(DirectX::SimpleMath::Vector3 vec) { m_acceleSpeed = vec; }

	// パーツ取得
	Object3D* GetRobotParts(Parts parts) { return m_robotParts[parts].get(); }
};
