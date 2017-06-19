/*
/	���͊֌W�\�[�X
/	Kai.Yamamoto
/	2017/06/12
*/

#include "Input.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace YamagenLib;

// �ÓI�����o�[�ϐ�
// �L�[�{�[�h
unique_ptr<Keyboard> Input::m_keybord = nullptr;
// �L�[�{�[�h�g���b�J�[
unique_ptr<Keyboard::KeyboardStateTracker> Input::m_keyTracker = nullptr;
// �}�E�X
unique_ptr<Mouse> Input::m_mouse = nullptr;
// �}�E�X�̃X�e�[�g
Mouse::State* Input::m_mouseState = nullptr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Input::Input()
{	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Input::~Input()
{
}

/// <summary>
/// ������
/// </summary>
void Input::Create()
{
	// �L�[�{�[�h
	m_keybord = make_unique<Keyboard>();
	// �L�[�{�[�h�g���b�J�[
	m_keyTracker = make_unique<Keyboard::KeyboardStateTracker>();
	
	// �}�E�X
	m_mouse = make_unique<Mouse>();
	// �X�e�[�g
	m_mouseState = new Mouse::State();
}

/// <summary>
/// �j��
/// </summary>
void Input::Destory()
{
	m_keyTracker.reset();	// �g���b�J�[

	m_mouse.reset();		// �}�E�X
	delete m_mouseState;	// �X�e�[�g
}

/// <summary>
/// �X�V����
/// </summary>
void Input::Update()
{
	// �g���b�J�[�X�V
	m_keyTracker->Update(Keyboard::Get().GetState());

	// �}�E�X�X�V
	m_mouseState = &m_mouse->GetState();
}

/// <summary>
/// �L�[��������Ă��邩�ǂ���
/// </summary>
/// <param name="key"> ���ʂ���L�[ </param>
/// <returns> �L�[�������Ă���� true ��Ԃ�</returns>
bool Input::GetKey(Key key)
{
	return Keyboard::Get().GetState().IsKeyDown(static_cast<Keyboard::Keys>(key));
}

/// <summary>
/// �L�[�������ꂽ���ǂ���
/// </summary>
/// <param name="key"> ���ʂ���L�[ </param>
/// <returns> �L�[���������t���[������ true ��Ԃ�</returns>
bool Input::GetKeyDown(Key key)
{
	return m_keyTracker->IsKeyPressed(static_cast<Keyboard::Keys>(key));
}

/// <summary>
/// �L�[�������ꂽ���ǂ���
/// </summary>
/// <param name="key"> ���ʂ���L�[ </param>
/// <returns> �L�[�𗣂����t���[������ true ��Ԃ�</returns>
bool Input::GetKeyUp(Key key)
{
	return m_keyTracker->IsKeyReleased(static_cast<Keyboard::Keys>(key));
}

/// <summary>
/// Windows procedure �p�@�֐�
/// </summary>
/// <param name="message">���b�Z�[�W</param>
/// <param name="wParam">���b�Z�[�W�̕t�����</param>
/// <param name="lParam">���b�Z�[�W�̕t�����</param>
void Input::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	// �L�[�{�[�h�̃��b�Z�[�W
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

	// �}�E�X�֌W�̃��b�Z�[�W
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
