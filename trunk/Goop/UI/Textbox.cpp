#include "Textbox.h"
#include "../MessageProxy.h"

using Goop::Textbox;

Textbox::Textbox(const wchar_t *text, Base *parent)
{
	m_proxy = new MessageProxy(this);

	HINSTANCE instanceHandle = GetModuleHandle( NULL );
	m_handle = (HWND)CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_proxy->m_handle, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	SetText(text);
}

Textbox::~Textbox()
{

}

void Textbox::SetMultiline(bool multiline)
{
	if(multiline)
		AddStyle(ES_MULTILINE);
	else
		RemoveStyle(ES_MULTILINE);
}

bool Textbox::GetMultiline()
{
	return (GetStyle() & ES_MULTILINE) > 0;
}

void Textbox::AppendText(const wchar_t *text)
{
	HWND currentFocus = ::GetFocus();

	SendMessage(m_handle, WM_SETFOCUS, (WPARAM)m_handle, 0);
	SendMessage(m_handle, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	SendMessage(m_handle, EM_REPLACESEL, 0, (LPARAM)text);

	if(currentFocus != 0)
		SetFocus(currentFocus);
}