// 
// 3DObjectのクラス
// K.Yamamoto
// 
#pragma once
#include <Effects.h>
#include <Model.h>
#include <simplemath.h>
#include <CommonStates.h>
#include <map>

static const float PI = 3.141592;

class Object3D
{
public :	// 定数
	static const float GRAVITY;	//重力

protected:
	// モデル
	DirectX::Model* m_model;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// デバイスのポインタ
	static ID3D11Device* m_pDevice;
	// コンテキストのポインタ
	static ID3D11DeviceContext* m_pContext;
	// エフェクトファクトリー
	static DirectX::EffectFactory* m_pEffectFactory;

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 回転角（オイラー角）
	DirectX::SimpleMath::Vector3 m_rotate;
	// 回転角（クォータニオン）
	DirectX::SimpleMath::Quaternion m_rotateQ;
	// スケール
	float m_scale;
	// 親のポインタ
	Object3D* m_pParent;
	// 回転をクォータニオンで持っているかのフラグ
	bool m_useQuternion;
private:	// static 
	// 読み込み済みモデルコンテナ
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> m_modelArray;

public:		// static
	// 初期化
	static void Initialize(ID3D11Device* d3ddevice, ID3D11DeviceContext* d3dcontext, DirectX::EffectFactory* effect);

	// デバイスの設定
	static void SetDevice(ID3D11Device* d3ddevice) { m_pDevice = d3ddevice; }
	// コンテキストの設定
	static void SetContext(ID3D11DeviceContext* d3dcontext) { m_pContext = d3dcontext; }
	// エフェクトファクトリーの設定
	static void SetEffectFactory(DirectX::EffectFactory* effect) { m_pEffectFactory = effect; }

public:
	// デフォルトコンストラクタ
	Object3D();
	Object3D(const wchar_t* fileName);
	Object3D(std::unique_ptr<DirectX::Model> model);
	virtual ~Object3D(){}

	// ファイルからモデルを読み込む
	DirectX::Model* LoadModelFile(const wchar_t*filename = nullptr);

	// 更新
	virtual void Update();

	// 描画
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)const;
	
	// ワールド座標
	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }

	// 移動
	void SetPosition(const DirectX::SimpleMath::Vector3& vec3) { m_position = vec3; }
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	
	// 回転角用
	void SetRotate(const DirectX::SimpleMath::Vector3& rotation) { m_rotate = rotation*DirectX::XM_2PI; m_useQuternion = false; }
	void SetRotateRadians(const DirectX::SimpleMath::Vector3& rotation) { m_rotate = rotation; m_useQuternion = false; }
	void SetRotateQ(const DirectX::SimpleMath::Quaternion& rotation) { m_rotateQ = rotation; m_useQuternion = true; }
	DirectX::SimpleMath::Vector3 GetRotate() { return m_rotate/DirectX::XM_2PI ; }
	DirectX::SimpleMath::Vector3 GetRotateRadians() { return m_rotate; }

	// スケール変更
	void SetScale(const float& scale) { m_scale = scale; }

	// 親関係
	void SetParent(Object3D* pObj) { m_pParent = pObj; }
	Object3D* GetParent() { return m_pParent; }
};

