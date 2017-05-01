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

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:
	static const int IN_BALL_NUM	= 10;	// 内側ボールの数
	static const int OUT_BALL_NUM	= 10;	// 外側ボールの数
	static const int IN_DIRECTION	= 15;	// 内側ボールの距離
	static const int OUT_DIRECTION	= 28;	// 外側ボールの距離

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
	std::unique_ptr<Object3D> m_ground;
	std::unique_ptr<Object3D> m_skyeDome;
	//std::unique_ptr<Object3D> m_mainBall;
	//std::unique_ptr<Object3D> m_inBall[IN_BALL_NUM];
	//std::unique_ptr<Object3D> m_outBall[OUT_BALL_NUM];
	std::unique_ptr<Object3D> m_teaPot[10];



	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

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


	// 時間
	float m_time;
	DirectX::SimpleMath::Vector3 m_startPos[10];

	DirectX::SimpleMath::Vector3 Lerp(
		DirectX::SimpleMath::Vector3 startPosition, 
		DirectX::SimpleMath::Vector3 targetPosition, float t)
	{
		DirectX::SimpleMath::Vector3 lerpPosition 
			= DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f);

		lerpPosition = (1 - t) * startPosition + t * targetPosition;

		return lerpPosition;
	}
};