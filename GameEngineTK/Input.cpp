/*
/	入力関係ソース
/	Kai.Yamamoto
/	2017/06/12
*/

#include "Input.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace YamagenLib;

// 静的メンバー変数
// キーボード
unique_ptr<Keyboard> Input::m_keybord = nullptr;
// キーボードトラッカー
unique_ptr<Keyboard::KeyboardStateTracker> Input::m_keyTracker = nullptr;
// マウス
unique_ptr<Mouse> Input::m_mouse = nullptr;
// マウスのステート
Mouse::State* Input::m_mouseState = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
Input::Input()
{	
}

/// <summary>
/// デストラクタ
/// </summary>
Input::~Input()
{
}

/// <summary>
/// 初期化
/// </summary>
void Input::Create()
{
	// キーボード
	m_keybord = make_unique<Keyboard>();
	// キーボードトラッカー
	m_keyTracker = make_unique<Keyboard::KeyboardStateTracker>();
	
	// マウス
	m_mouse = make_unique<Mouse>();
	// ステート
	m_mouseState = new Mouse::State();
}

/// <summary>
/// 破棄
/// </summary>
void Input::Destory()
{
	m_keyTracker.reset();	// トラッカー

	m_mouse.reset();		// マウス
	delete m_mouseState;	// ステート
}

/// <summary>
/// 更新処理
/// </summary>
void Input::Update()
{
	// トラッカー更新
	m_keyTracker->Update(Keyboard::Get().GetState());

	// マウス更新
	m_mouseState = &m_mouse->GetState();
}

/// <summary>
/// キーが押されているかどうか
/// </summary>
/// <param name="key"> 識別するキー </param>
/// <returns> キーを押している間 true を返す</returns>
bool Input::GetKey(Key key)
{
	return Keyboard::Get().GetState().IsKeyDown(static_cast<Keyboard::Keys>(key));
}

/// <summary>
/// キーが押されたかどうか
/// </summary>
/// <param name="key"> 識別するキー </param>
/// <returns> キーを押したフレームだけ true を返す</returns>
bool Input::GetKeyDown(Key key)
{
	return m_keyTracker->IsKeyPressed(static_cast<Keyboard::Keys>(key));
}

/// <summary>
/// キーが離されたかどうか
/// </summary>
/// <param name="key"> 識別するキー </param>
/// <returns> キーを離したフレームだけ true を返す</returns>
bool Input::GetKeyUp(Key key)
{
	return m_keyTracker->IsKeyReleased(static_cast<Keyboard::Keys>(key));
}

/// <summary>
/// Windows procedure 用　関数
/// </summary>
/// <param name="message">メッセージ</param>
/// <param name="wParam">メッセージの付加情報</param>
/// <param name="lParam">メッセージの付加情報</param>
void Input::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	// キーボードのメッセージ
	switch (message)
	{
	case WM_ACTIVATEAPP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	}

	// マウス関係のメッセージ
	switch (message)
	{
	case WM_ACTIVATEAPP:
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(message, wParam, lParam);
		break;
	}
}
