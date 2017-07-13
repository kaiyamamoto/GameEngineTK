// 
// 3DObjectのクラス
// K.Yamamoto
// 

#include "pch.h"
#include "Object3D.h"

// 名前空間
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 定数宣言
const float Object3D::GRAVITY = -1.633f / 60.0f;

// 静的変数宣言
ID3D11Device*			Object3D::m_pDevice;	// デバイスのポインタ
ID3D11DeviceContext*	Object3D::m_pContext;	// コンテキストのポインタ
DirectX::EffectFactory* Object3D::m_pEffectFactory;	// エフェクトファクトリー
// 読み込み済みモデルコンテナ
map<wstring,unique_ptr<Model>> Object3D::m_modelArray;

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
Object3D::Object3D()
	: m_model(nullptr)
	, m_position(Vector3(0.0f, 0.0f, 0.0f))
	, m_eulerAngles(Vector3(0.0f, 0.0f, 0.0f))
	, m_scale(1.0f)
	, m_pParent(nullptr)
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fileName">モデルのファイル名</param>
/// <param name="factory">エフェクトファクトリー</param>
Object3D::Object3D(const wchar_t * fileName)
	:Object3D()
{
	// モデルのロード
	m_model = LoadModelFile(fileName);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fileName">モデルポインタ</param>
Object3D::Object3D(unique_ptr<Model> model)
	:Object3D()
{
	// モデルのロード
	m_model = model.get();
}

/// <summary>
/// ファイルからモデルをロード
/// </summary>
/// <param name="filename">モデルのパス</param>
/// <returns>モデル</returns>
DirectX::Model* Object3D::LoadModelFile(const wchar_t*filename)
{
	assert(m_pEffectFactory);

	// 同じ名前のモデルを読み込み済みでなければひｔ
	if (m_modelArray.count(filename) == 0)
	{
		// モデルを読み込み、コンテナに登録（キーはファイル名）
		m_modelArray[filename] = Model::CreateFromCMO(m_pDevice, filename, *m_pEffectFactory);
	}
	return m_modelArray[filename].get();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="d3ddevice">デバイス</param>
/// <param name="d3dcontext">コンテキスト</param>
void Object3D::Initialize(ID3D11Device * d3ddevice, ID3D11DeviceContext * d3dcontext, EffectFactory* effect)
{
	// デバイスの設定
	SetDevice(d3ddevice);
	// コンテキストの設定
	SetContext(d3dcontext);
	// エフェクトファクトリー
	SetEffectFactory(effect);
}

void Object3D::LoadModel(const wchar_t * fileName)
{
	m_model = LoadModelFile(fileName);

}


/// <summary>
/// 更新
/// </summary>
void Object3D::Update()
{
	Matrix scaleMatrix, rotateMatrix, transMatrix;

	// スケール
	scaleMatrix = Matrix::CreateScale(m_scale);

	// 回転行列
	if (m_useQuternion)
	{// クォータニオンから回転行列を計算
		rotateMatrix = Matrix::CreateFromQuaternion(m_rotateQuaternion);
	}
	else
	{// オイラー角から回転行列を計算（Z→X→Y）
		rotateMatrix *= Matrix::CreateRotationZ(m_eulerAngles.z);
		rotateMatrix *= Matrix::CreateRotationX(m_eulerAngles.x);
		rotateMatrix *= Matrix::CreateRotationY(m_eulerAngles.y);
	}
	// 移動
	transMatrix = Matrix::CreateTranslation(m_position);
	// 演算
	m_world = scaleMatrix*rotateMatrix*transMatrix;
	// 親の行列をかける
	if (m_pParent){
		m_world *= m_pParent->GetWorld();
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="state">コモンステート</param>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Object3D::Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	m_model->Draw(m_pContext, state, m_world, view, proj);
}
