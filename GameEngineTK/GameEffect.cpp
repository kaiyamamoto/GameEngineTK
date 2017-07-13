#include "pch.h"
#include "GameEffect.h"

ID3D11Device* GameEffect::m_pDevice;
// コンテキストのポインタ
ID3D11DeviceContext* GameEffect::m_pContext;

using namespace Effekseer;
using namespace EffekseerRendererDX11;

/// <summary>
/// コンストラクタ
/// </summary>
GameEffect::GameEffect(wchar_t path[], float x, float y, float z)
	:cnt(0)
	, flag(false)
{
	// 描画管理インスタンスの生成
	m_renderer = Renderer::Create(m_pDevice, m_pContext, 256);
	
	// エフェクト管理用インスタンスの生成
	m_manager = Manager::Create(10);

	// 描画方法の指定
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	// テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	// 座標系の指定(RHで右手系、LHで左手系)
	m_manager->SetCoordinateSystem(CoordinateSystem::RH);

	// エフェクトの読込
	m_effect = Effekseer::Effect::Create(m_manager, (EFK_CHAR*)path);
	// エフェクトの再生
	m_handle = m_manager->Play(m_effect, x, y, z);
	//m_manager->SetScale(m_handle, 0.5f, 0.5f, 0.5f);
}

/// <summary>
/// デストラクタ
/// </summary>
GameEffect::~GameEffect()
{
	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	ES_SAFE_RELEASE(m_effect);
	// エフェクト管理用インスタンスを破棄
	m_manager->Destroy();
	// 描画用インスタンスを破棄
	m_renderer->Destory();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="context">コンテキスト</param>
void GameEffect::Initialize(ID3D11Device * device, ID3D11DeviceContext * context)
{
	m_pDevice = device;
	m_pContext = context;
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void GameEffect::Draw(const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)
{
	Effekseer::Matrix44 view44;
	Effekseer::Matrix44 proj44;

	float viewMatrix[4][4]={
		{ view._11,view._12,view._13,view._14 },
		{ view._21,view._22,view._23,view._24 },
		{ view._31,view._32,view._33,view._34 },
		{ view._41,view._42,view._43,view._44 }
	};
	float projMatrix[4][4] = {
		{ proj._11,proj._12,proj._13,proj._14 },
		{ proj._21,proj._22,proj._23,proj._24 },
		{ proj._31,proj._32,proj._33,proj._34 },
		{ proj._41,proj._42,proj._43,proj._44 }
	};


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			view44.Values[i][j] = viewMatrix[i][j];
			proj44.Values[i][j] = projMatrix[i][j];
		}
	}

	// 投影行列の更新
	m_renderer->SetProjectionMatrix(proj44);
	// カメラ行列の更新
	m_renderer->SetCameraMatrix(view44);
	// 再生中のエフェクトの移動等(Effekseer::Manager経由で様々なパラメーターが設定できます。)
	//m_manager->AddLocation(m_handle, Effekseer::Vector3D);
	// 全てのエフェクトの更新
	
	m_manager->Update();

	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();

	cnt++;

	if (cnt > 600) flag = true;
}
