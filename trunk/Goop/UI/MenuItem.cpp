#include "Menu.h"
#include "../Bitmap.h"

using namespace Goop;

MenuItem::MenuItem(Menu *parent, const wchar_t *text) : m_text(0)
{
	m_parent = parent;

	if(text != 0)
		m_text = _wcsdup(text);

}

MenuItem::MenuItem(Menu *parent) : m_text(0)
{
	m_parent = parent;
}

MenuItem::~MenuItem()
{
	DeleteMenu(m_parent->m_handle, (UINT)this, MF_BYCOMMAND);

	if(m_text != 0)
		free(m_text);

	if(m_parent != 0)
	{
		for(unsigned int i = 0; i < m_parent->m_childItems.size(); i++)
		{
			if(m_parent->m_childItems[i] == this)
			{
				m_parent->m_childItems.erase(m_parent->m_childItems.begin() + i);
				break;
			}
		}
	}
}

void MenuItem::SetChecked(bool checked)
{
	::CheckMenuItem(m_parent->m_handle, (UINT)this, MF_BYCOMMAND | (checked ? MF_CHECKED : MF_UNCHECKED));
}

bool MenuItem::GetChecked()
{
	return (::GetMenuState(m_parent->m_handle, (UINT)this, MF_BYCOMMAND) & MF_CHECKED) > 0;
}

const wchar_t *MenuItem::GetText()
{
	return m_text;
}

void MenuItem::SetText(const wchar_t *text)
{
	if(m_parent == 0)
		return;

	if(OnTextChanged(text, m_text))
		return;

	if(m_text != 0)
		free(m_text);

	if(text != 0)
		m_text = _wcsdup(text);
	else
		m_text = 0;
	
	MENUITEMINFOW info;
	info.cbSize = sizeof(MENUITEMINFOW);
	info.fMask = MIIM_STRING;
	info.cch = wcslen(text);
	info.dwTypeData = m_text;
	SetInfo(info);
}

void MenuItem::SetImages(Bitmap *checked, Bitmap *unchecked)
{
	if(m_parent == 0)
		return;

	MENUITEMINFOW info;
	info.cbSize = sizeof(MENUITEMINFOW);
	info.fMask = MIIM_CHECKMARKS;	
	info.hbmpChecked = (HBITMAP)checked->GetHandle();
	info.hbmpUnchecked = (HBITMAP)unchecked->GetHandle();

	::SetMenuItemInfo(m_parent->m_handle, (UINT)this, false, &info);
}

void MenuItem::SetInfo(MENUITEMINFOW info)
{
	::SetMenuItemInfo(m_parent->m_handle, (UINT)this, false, &info);
}

MENUITEMINFOW MenuItem::GetInfo(DWORD mask)
{
	MENUITEMINFOW info;
	info.cbSize = sizeof(MENUITEMINFOW);
	info.fMask = mask;
	::GetMenuItemInfo(m_parent->m_handle, (UINT)this, false, &info);

	return info;
}

bool MenuItem::OnTextChanged(const wchar_t *newText,const wchar_t *oldText)
{

	return false;
}

bool MenuItem::OnMouseClick(MouseButton button)
{
	return false;
}