#include "Textbox.h"
#include "../MessageProxy.h"

using Goop::Textbox;

void Textbox::SwitchMode(const wchar_t *text, Base *parent, DWORD style)
{
	Vector2D pos = GetPosition();
	Vector2D size = GetSize();
	SetParent(0);
	Destroy();

	if(m_proxy != 0)
		delete m_proxy;

	m_proxy = new MessageProxy(this);

	HINSTANCE instanceHandle = GetModuleHandle( NULL );
	m_handle = (HWND)CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_proxy->m_handle, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	SetText(text);

	SetPosition(pos);
	SetSize(size);
}

Textbox::Textbox(const wchar_t *text, Base *parent) : m_proxy(0)
{
	SwitchMode(text, parent, WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL);
	SetParent(parent);
	SetText(text);
}

Textbox::~Textbox()
{

}

void Textbox::SetMultiline(bool multiline)
{
	if(multiline)
		SwitchMode(GetText(), GetParent(), GetStyle() | ES_MULTILINE);
	else
		SwitchMode(GetText(), GetParent(), GetStyle() & (~ES_MULTILINE));
}

bool Textbox::GetMultiline()
{
	return (GetStyle() & ES_MULTILINE) > 0;
}

void Textbox::SetPasswordCharacter(wchar_t character)
{
	::SendMessageW(m_handle, EM_SETPASSWORDCHAR, (WPARAM)character, 0);
}

wchar_t Textbox::GetPasswordCharacter()
{
	return (wchar_t)::SendMessageW(m_handle, EM_GETPASSWORDCHAR, 0, 0);
}

void Textbox::AppendText(const wchar_t *text)
{
	HWND currentFocus = ::GetFocus();

	SetFocus(m_handle);
	SendMessage(m_handle, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	SendMessage(m_handle, EM_REPLACESEL, 0, (LPARAM)text);

	if(currentFocus != 0)
		SetFocus(currentFocus);
}