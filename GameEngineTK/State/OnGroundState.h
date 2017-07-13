#pragma once
#include "RobotState.h"

class OnGroundState :
	public RobotState
{
private:
	OnGroundState():m_isWalke(false) {}
	static OnGroundState* m_instance;
	// テクスチャハンドル
	ComPtr<ID3D11ShaderResourceView> texture;

	float m_time;
	bool m_isWalke;
public:
	// シングルトン
	static OnGroundState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new OnGroundState();
		}
		return m_instance;
	}

	void Enter(Robot& robot)override;
	RobotState* HandleInput(Robot& robot)override;
	void Update(Robot& robot) override;
	void Exit(Robot& robot) override;


	// Lerp
	DirectX::SimpleMath::Vector3 Lerp(
		DirectX::SimpleMath::Vector3 startPosition,
		DirectX::SimpleMath::Vector3 targetPosition, float t){
		return (1 - cosCurve(t)) * startPosition + cosCurve(t) * targetPosition;
	}
	float cosCurve(float time) { return (1 - std::cos(time * PI)) / 2; }

};