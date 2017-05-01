// 
// 3DObjectのクラス
// K.Yamamoto
// 

#include "pch.h"
#include "Object3D.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的変数宣言
ID3D11Device*			Object3D::m_pDevice;	// デバイスのポインタ
ID3D11DeviceContext*	Object3D::m_pContext;	// コンテキストのポインタ


Object3D::Object3D(const wchar_t * fileName, DirectX::EffectFactory & factory)
	:m_position(Vector3(0.0f,0.0f,0.0f))
	,m_rotate(Vector3(0.0f,0.0f,0.0f))
	,m_scale(1.0f)
{
	// モデルのロード
	m_model = Model::CreateFromCMO(m_pDevice, fileName, factory);
}

Object3D::~Object3D()
{
}

// デバイスの設定
void Object3D::SetDevice(ID3D11Device* d3ddevice)
{
	m_pDevice = d3ddevice;
}

// コンテキストの設定
void Object3D::SetContext(ID3D11DeviceContext * d3dcontext)
{
	m_pContext = d3dcontext;
}

// 更新
void Object3D::Update()
{
	Matrix scaleMatrix, rotateMatrix, transMatrix;

	// スケール
	scaleMatrix = Matrix::CreateScale(m_scale);
	// 回転
	rotateMatrix *= Matrix::CreateRotationX(m_rotate.x*XM_2PI);
	rotateMatrix *= Matrix::CreateRotationY(m_rotate.y*XM_2PI);
	rotateMatrix *= Matrix::CreateRotationZ(m_rotate.z*XM_2PI);
	// 移動
	transMatrix = Matrix::CreateTranslation(m_position);

	// 演算
	m_world = scaleMatrix*rotateMatrix*transMatrix;
}

// 描画
void Object3D::Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj) const
{
	m_model->Draw(m_pContext, state, m_world, view, proj);
}
