/// <summary>
/// GameEffect
/// </summary>

#include<simplemath.h>
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <d3d11.h>

#pragma once
class GameEffect
{
private:
	int cnt;
	bool flag;

	// デバイスのポインタ
	static ID3D11Device* m_pDevice;
	// コンテキストのポインタ
	static ID3D11DeviceContext* m_pContext;

	EffekseerRenderer::Renderer* m_renderer;
	Effekseer::Manager* m_manager;
	Effekseer::Effect* m_effect;
	Effekseer::Handle m_handle;

public:
	GameEffect(wchar_t path[], float x, float y, float z);
	~GameEffect();

	static void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

	// 描画
	void Draw(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	bool IsEnd() { return flag; }
};

