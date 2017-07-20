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

#include <SpriteBatch.h>
#include <SpriteFont.h>

static const float PI = 3.141592;

using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Quaternion;

class Object3D
{
public :	// 定数

	static const float GRAVITY;	//重力

protected:	// 静的変数

	// デバッグ用
	static std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	static std::unique_ptr<DirectX::SpriteFont> spriteFont;

	// デバイスのポインタ
	static ID3D11Device* m_pDevice;
	// コンテキストのポインタ
	static ID3D11DeviceContext* m_pContext;
	// エフェクトファクトリー
	static DirectX::EffectFactory* m_pEffectFactory;

protected:	// 変数

	// モデル
	DirectX::Model* m_model;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// 座標
	Vector3 m_position;
	// 回転角（オイラー角）
	Vector3 m_eulerAngles;
	// 回転角（クォータニオン）
	Quaternion m_rotateQuaternion;
	// スケール
	Vector3 m_scale;
	// 親のポインタ
	Object3D* m_pParent;
	// 回転をクォータニオンで持っているかのフラグ
	bool m_useQuternion;

private:	// 静的変数
	// 読み込み済みモデルコンテナ
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> m_modelArray;

public:		// static関数

	// 初期化
	static void Initialize(ID3D11Device* d3ddevice, ID3D11DeviceContext* d3dcontext, DirectX::EffectFactory* effect);
	// デバイスの設定
	static void SetDevice(ID3D11Device* d3ddevice) { m_pDevice = d3ddevice; spriteFont = std::make_unique<DirectX::SpriteFont>(m_pDevice, L"myfile.spritefont");}
	// コンテキストの設定
	static void SetContext(ID3D11DeviceContext* d3dcontext) { m_pContext = d3dcontext; spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_pContext);}
	// エフェクトファクトリーの設定
	static void SetEffectFactory(DirectX::EffectFactory* effect) { m_pEffectFactory = effect; }

public:		// 関数

	// コンストラクタ
	Object3D();
	Object3D(const wchar_t* fileName);
	Object3D(std::unique_ptr<DirectX::Model> model);

	// デストラクタ
	virtual ~Object3D(){}

	// ファイルからモデルを読み込む
	DirectX::Model* LoadModelFile(const wchar_t*filename = nullptr);

	// モデルのロード
	void LoadModel(const wchar_t * fileName);

	// 更新
	virtual void Update();

	virtual void Calc();

	// 描画
	virtual void Draw(const DirectX::CommonStates& state, const Matrix& view, const Matrix& proj)const;

	// ワールド座標
	Matrix GetWorld()						{ return m_world;	 }
	void SetWorld(const Matrix& mat) { m_world = mat; }
	
	// 移動
	void SetPosition(const Vector3& vec3)	{ m_position = vec3; }
	void SetPositionX(const float& vec) { m_position.x = vec; }
	void SetPositionY(const float& vec) { m_position.y = vec; }
	void SetPositionZ(const float& vec) { m_position.z = vec; }
	Vector3 GetPosition()					{ return m_position; }
	
	// 回転角
	void SetEulerAngle(const Vector3& rotation)			{ m_eulerAngles = rotation*DirectX::XM_2PI; m_useQuternion = false; }
	void SetEulerAngleRadians(const Vector3& rotation)	{ m_eulerAngles = rotation; m_useQuternion = false; }
	void SetRotation(const Quaternion& rotation)		{ m_rotateQuaternion = rotation; m_useQuternion = true; }
	Vector3 GetEulerAngle()								{ return m_eulerAngles / DirectX::XM_2PI; }
	Vector3 GetEulerAngleRadians()						{ return m_eulerAngles; }
	const Quaternion& GetRotation()						{ return m_rotateQuaternion; }

	// スケール
	void SetScale(const float& scale) { m_scale = Vector3(scale); }
	void SetScale(const Vector3& scale) { m_scale = scale; }
	void SetScaleX(const float& scale) { m_scale.x = scale; }
	void SetScaleY(const float& scale) { m_scale.y = scale; }
	void SetScaleZ(const float& scale) { m_scale.z = scale; }
	Vector3 GetScale() { return m_scale; }

	// 親関係
	void SetParent(Object3D* pObj) { m_pParent = pObj; }
	Object3D* GetParent() { return m_pParent; }

	// 当たった時の処理
	virtual void OnCollisionEnter(const Object3D& obj){}
};

