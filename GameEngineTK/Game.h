//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <VertexTypes.h>
#include <Effects.h>
#include <list>
#include <Mouse.h>
#include <CommonStates.h>
#include <simplemath.h>
#include "DebugCamera.h"
#include <Model.h>
#include "Object3D.h"
#include "FollowCamera.h"
#include "PlayerRobot.h"
#include "EnemyRobot.h"
#include "GameEffect.h"
#include "LandShape.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

private:
	std::unique_ptr<DirectX::BasicEffect>		m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
	std::unique_ptr<DirectX::CommonStates>		m_states;

	// エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;

	DirectX::SimpleMath::Matrix m_world;	// ワールド行列
	DirectX::SimpleMath::Matrix m_view;		// ビュー行列
	DirectX::SimpleMath::Matrix m_proj;		// 射影行列

	// モデル
	//std::unique_ptr<Object3D> m_ground;
	std::unique_ptr<Object3D> m_skyeDome;
	// 地形
	LandShape m_LandShape;

	// プレイヤー
	std::unique_ptr<PlayerRobot> m_Player;

	// 敵
	std::vector<std::unique_ptr<EnemyRobot>> m_enemies;

	// カメラ
	std::unique_ptr<Camera> m_camera;

	// エフェクトリスト
	std::list<GameEffect*> m_effectList;
public:
    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};