//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <CommonStates.h>
#include <simplemath.h>
#include <random>
#include <time.h>    

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;
using VC = VertexPositionColor;

static const int WINDOW_W = 800;
static const int WINDOW_H = 600;

Game::Game() :
    m_window(0),
    m_outputWidth(WINDOW_W),
    m_outputHeight(WINDOW_H),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	// Object3Dの設定
	Object3D::SetContext(m_d3dContext.Get());
	Object3D::SetDevice(m_d3dDevice.Get());

	// メンバの作成
	// effectの作成
	m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());
	// 設定
	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0,
		m_outputWidth, m_outputHeight, 0, 0, 1));
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	// エフェクトファクトリの作成
	m_effectFactory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// テクスチャの場所を指定
	m_effectFactory->SetDirectory(L"Resources");
	// オブジェクトの読み込み
	m_ground = std::make_unique<Object3D>(L"Resources\\ground.cmo", *m_effectFactory);
	m_skyeDome = std::make_unique<Object3D>(L"Resources\\skydome.cmo", *m_effectFactory);
	
	std::random_device rnd;     // 非決定的な乱数生成器を生成
	std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
	std::uniform_int_distribution<> rand100(-20, 20);        // [0, 99] 範囲の一様乱数
	for (int i = 0; i < 10; i++)
	{
		m_teaPot[i] = std::make_unique<Object3D>(L"Resources\\teapot.cmo", *m_effectFactory);
		float posX = static_cast<float>(rand100(mt));
		float posZ = static_cast<float>(rand100(mt));
		m_teaPot[i]->SetPosition(Vector3(posX, 0.0f, posZ));
	}

	m_time = clock()/1000.0f;
	for (int i = 0; i < 10; i++) {
		m_startPos[i] = m_teaPot[i]->GetPosition();
	}

	//m_mainBall = std::make_unique<Object3D>(L"Resources\\ball.cmo", *m_effectFactory);
	//for (int i = 0; i < IN_BALL_NUM; i++)
	//	m_inBall[i] = std::make_unique<Object3D>(L"Resources\\ball.cmo", *m_effectFactory);
	//for (int i = 0; i < OUT_BALL_NUM; i++)
	//	m_outBall[i] = std::make_unique<Object3D>(L"Resources\\ball.cmo", *m_effectFactory);

	// デバッグカメラの生成
	m_debugCamera = std::make_unique<DebugCamera>(m_outputWidth, m_outputHeight);
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	// ゲームの毎フレーム処理
	// デバッグカメラの更新
	m_debugCamera->Update();

	static float rotate = 0.0f;
	rotate += 0.01f;
	if (360.0f < rotate)
		rotate = 0.0f;

	static float scale = 5.0f;
	static bool scaleFlag = true;
	if (scaleFlag) {
		scale -= 0.02f;
		if (scale < 1.0f)
			scaleFlag = false;
	}
	else {
		scale += 0.02f;
		if (scale > 5.0f)
			scaleFlag = true;
	}

	for (int i = 0; i < 10; i++)
	{
		m_teaPot[i]->SetRotate(Vector3(0.0f, rotate, 0.0f));
		m_teaPot[i]->SetScale(scale);
		float timeStep = (clock() / 1000.0f - m_time / 1000.0f) / 10.0f;
		if (timeStep < 1.0f)
		{
			m_teaPot[i]->SetPosition(Lerp(m_startPos[i], Vector3(0.0f, 0.0f, 0.0f), timeStep));
		}
		m_teaPot[i]->Update();
	}

	//static float inPosGap = 0.0f;
	//inPosGap -= 0.02f;
	//if (-360.0f > inPosGap)
	//	inPosGap = 0.0f;
	//static float outPosGap = 0.0f;
	//outPosGap += 0.02f;
	//if (360.0f < outPosGap)
	//	outPosGap = 0.0f;
	//// 内側ボール
	//float angleDiff = 360.0f / IN_BALL_NUM;
	//float angle = (90 * XM_2PI / 360) + inPosGap;
	//// 真ん中ボール
	//m_mainBall->SetScale(3.0f);
	//m_mainBall->SetRotate(Vector3(0.0f,angle/6,0.0f));
	//m_mainBall->Update();
	//for (int i = 0; i < IN_BALL_NUM; i++)
	//{
	//	Vector3 postion = Vector3(0.0f, 0.0f, 0.0f);
	//	angle = ((90 - angleDiff * i) * XM_2PI / 360) + inPosGap;
	//	postion.x += IN_DIRECTION * cosf(angle);
	//	postion.z += IN_DIRECTION * sinf(angle);
	//	m_inBall[i]->SetPosition(postion);
	//	m_inBall[i]->SetScale(0.8f);
	//	m_inBall[i]->SetRotate(Vector3(0.0f, angle/6, 0.0f));
	//	// ボールの更新
	//	m_inBall[i]->Update();
	//}
	//// 外側ボール
	//angleDiff = 360.0f / OUT_BALL_NUM;
	//for (int i = 0; i < OUT_BALL_NUM; i++)
	//{
	//	Vector3 postion = Vector3(0.0f, 0.0f, 0.0f);
	//	angle = ((90 - angleDiff * i) * XM_2PI / 360) + outPosGap;
	//	postion.x += OUT_DIRECTION * cosf(angle);
	//	postion.z += OUT_DIRECTION * sinf(angle);
	//	m_outBall[i]->SetPosition(postion);
	//	m_outBall[i]->SetRotate(Vector3(0.0f, angle/6, 0.0f));
	//	// ボールの更新
	//	m_outBall[i]->Update();
	//}
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();
    // TODO: Add your rendering code here.	
	// 描画はここに書く。
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
	m_d3dContext->RSSetState(m_states->Wireframe());

	//m_view = Matrix::CreateLookAt(Vector3(0, 2.f, 2.f),
	//	Vector3(0,0,0), Vector3(0,1,0));
	// デバッグカメラからビュー行列を取得
	m_view = m_debugCamera->GetCameraMatrix();

	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(m_outputWidth) / float(m_outputHeight), 0.1f, 1000.f);

	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);
	m_effect->Apply(m_d3dContext.Get());
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	// モデルの描画
	m_ground->Draw(*m_states, m_view, m_proj);
	m_skyeDome->Draw(*m_states, m_view, m_proj);

	for (int i = 0; i < 10; i++)
	{
		m_teaPot[i]->Draw(*m_states, m_view, m_proj);
	}

	//m_mainBall->Draw(*m_states, m_view, m_proj);
	//// 球の描画
	//for (int i = 0; i < IN_BALL_NUM; i++)
	//	m_inBall[i]->Draw(*m_states, m_view, m_proj);
	//for (int i = 0; i < OUT_BALL_NUM; i++)
	//	m_outBall[i]->Draw(*m_states, m_view, m_proj);

	Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = WINDOW_W;
    height = WINDOW_H;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}