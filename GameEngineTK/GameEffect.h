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

	// �f�o�C�X�̃|�C���^
	static ID3D11Device* m_pDevice;
	// �R���e�L�X�g�̃|�C���^
	static ID3D11DeviceContext* m_pContext;

	EffekseerRenderer::Renderer* m_renderer;
	Effekseer::Manager* m_manager;
	Effekseer::Effect* m_effect;
	Effekseer::Handle m_handle;

public:
	GameEffect(wchar_t path[], float x, float y, float z);
	~GameEffect();

	static void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

	// �`��
	void Draw(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	bool IsEnd() { return flag; }
};

