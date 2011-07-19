#include "Button.h"

using Goop::Button;

Button::Button(const wchar_t *text, Base *parent)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );

	m_handle = (HWND)CreateWindowExW(0, L"BUTTON", L"", WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	SetText(text);
}

Button::~Button()
{

}