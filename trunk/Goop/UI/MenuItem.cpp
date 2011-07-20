#include "Menu.h"
#include "../Bitmap.h"

using namespace Goop;

MenuItem::MenuItem(Menu *parent, const wchar_t *text) : m_parent(0), m_text(0), m_bitmap(0)
{
	if(parent != 0)
	{
		m_parent = parent;
		m_text = _wcsdup(text);

		MENUITEMINFOW info;
		info.cbSize = sizeof(MENUITEMINFOW);
		info.fMask = MIIM_ID | MIIM_DATA | MIIM_STRING | MIIM_FTYPE | MIIM_STATE;
		info.wID = (UINT)this;
		info.dwItemData = (DWORD)this;
		info.dwTypeData = (wchar_t *)m_text;
		info.cch = wcslen(m_text) + 1;
		info.fState = MFS_UNCHECKED;
		info.fType = MFT_STRING;

		InsertMenuItemW(parent->m_handle, (UINT)this, false, &info);
	}
}

MenuItem::MenuItem()
{

}

void MenuItem::SetText(const wchar_t *text)
{
	if(m_text)
		free(m_text);

	if(text != 0)
		m_text = _wcsdup(text);

	MENUITEMINFOW info;
	info.cbSize = sizeof(MENUITEMINFOW);
	info.fMask = MIIM_STRING;
	info.cch = wcslen(text);
	info.dwTypeData = m_text;
	::SetMenuItemInfo(m_parent->m_handle, (UINT)this, false, &info);
}

const wchar_t *MenuItem::GetText()
{
	return m_text;
}

void MenuItem::SetChecked(bool checked)
{
	::CheckMenuItem(m_parent->m_handle, (UINT)this, MF_BYCOMMAND | (checked ? MF_CHECKED : MF_UNCHECKED));
}

bool MenuItem::GetChecked()
{
	return (::GetMenuState(m_parent->m_handle, (UINT)this, MF_BYCOMMAND) & MF_CHECKED) > 0;
}

bool MenuItem::OnTextChanged(const wchar_t *newText,const wchar_t *oldText)
{
	return false;
}

bool MenuItem::OnMouseClick(MouseButton button)
{
	return false;
}