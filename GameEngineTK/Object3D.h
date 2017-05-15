// 
// 3DObjectのクラス
// K.Yamamoto
// 
#include <Effects.h>
#include <Model.h>
#include <simplemath.h>
#include <CommonStates.h>

#pragma once
class Object3D
{
private:
	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// デバイスのポインタ
	static ID3D11Device* m_pDevice;
	// コンテキストのポインタ
	static ID3D11DeviceContext* m_pContext;

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 回転
	DirectX::SimpleMath::Vector3 m_rotate;
	// スケール
	float m_scale;

public:
	Object3D(const wchar_t* fileName,DirectX::EffectFactory& factory);
	~Object3D();

	// デバイスの設定
	static void SetDevice(ID3D11Device* d3ddevice);
	// コンテキストの設定
	static void SetContext(ID3D11DeviceContext* d3dcontext);

	// 更新
	virtual void Update();

	// 描画
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)const;
	
	// 移動
	void SetPosition(const DirectX::SimpleMath::Vector3& vec3) { m_position = vec3; }
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	
	// 回転
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { m_rotate = rotate; }
	DirectX::SimpleMath::Vector3 GetRotate() { return m_rotate; }

	// スケール変更
	void SetScale(const float& scale) { m_scale = scale; }
};

