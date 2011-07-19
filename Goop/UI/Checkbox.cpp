#include "Checkbox.h"
#include "../MessageProxy.h"

using Goop::Checkbox;

static unsigned int g_checkId = 100000;

Checkbox::Checkbox(const wchar_t *text, Base *parent)
{
	m_id = ++g_checkId;
	m_proxy = new MessageProxy(this);

	HINSTANCE instanceHandle = GetModuleHandle(0);
	m_handle = (HWND)CreateWindowExW(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_proxy->m_handle, (HMENU)m_id, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	SetText(text);
}

Checkbox::~Checkbox()
{

}

bool Checkbox::GetChecked()
{
	return (bool)(::IsDlgButtonChecked(m_parent->GetHandle(), m_id) == BST_CHECKED);
}

void Checkbox::SetChecked(bool checked)
{
	::CheckDlgButton(m_parent->GetHandle(), m_id, checked ? BST_CHECKED : BST_UNCHECKED);
}

bool Checkbox::OnChecked()
{
	return false;
}

bool Checkbox::OnUnchecked()
{
	return false;
}