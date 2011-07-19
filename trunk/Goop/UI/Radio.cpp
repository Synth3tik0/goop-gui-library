#include "Radio.h"
#include "../MessageProxy.h"

using Goop::Radio;

static unsigned int g_radioId = 0;

Radio::Radio(const wchar_t *text, Base *parent)
{
	m_id = ++g_radioId;
	m_proxy = new MessageProxy(this);

	HINSTANCE instanceHandle = GetModuleHandle(0);
	m_handle = (HWND)CreateWindowExW(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_proxy->m_handle, (HMENU)m_id, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	SetText(text);
}

Radio::~Radio()
{

}

bool Radio::GetChecked()
{
	return (bool)(::IsDlgButtonChecked(m_parent->GetHandle(), m_id) == BST_CHECKED);
}

void Radio::SetChecked(bool checked)
{
	::CheckDlgButton(m_parent->GetHandle(), m_id, checked ? BST_CHECKED : BST_UNCHECKED);
}

bool Radio::OnChecked()
{
	return false;
}

bool Radio::OnUnchecked()
{
	return false;
}