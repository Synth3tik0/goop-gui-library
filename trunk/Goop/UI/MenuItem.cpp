#include "Menu.h"
#include "../Bitmap.h"

using namespace Goop;

void MenuItem::InitializeInfo()
{
	memset(&m_info, 0, sizeof(MENUITEMINFOW));
	m_info.cbSize = sizeof(MENUITEMINFOW);
	m_info.fMask = MIIM_SUBMENU | MIIM_DATA | MIIM_STRING | MIIM_FTYPE | MIIM_STRING | MIIM_BITMAP | MIIM_CHECKMARKS | MIIM_ID | MIIM_STATE;
	m_info.dwItemData = (ULONG_PTR)this;
	m_info.dwTypeData = 0;
	m_info.cch = 0;
	m_info.wID = (ULONG_PTR)this;
	m_info.hSubMenu = 0;
	m_info.hbmpChecked = 0;
	m_info.hbmpUnchecked = 0;
	m_info.hbmpItem = 0;
	m_info.fType = 0;
	m_info.fState = MFS_ENABLED | MFS_UNCHECKED;
}

MenuItem::MenuItem(const wchar_t *text) : m_parent(0), m_position(0)
{
	InitializeInfo();

	if(text != 0)
	{
		m_info.dwTypeData = _wcsdup(text);
		m_info.cch = wcslen(text) + 1;
	}
}

MenuItem::MenuItem(Bitmap *bitmap) : m_parent(0)
{
	InitializeInfo();

	if(bitmap != 0)
	{
		m_info.hbmpItem = (HBITMAP)bitmap->GetHandle();
	}
}

MenuItem::~MenuItem()
{

}

void MenuItem::SetMenu(Menu *menu)
{
	/********************************************
	* Due to undefined behaviour in the WinAPI, *
	* which DELETES any pre-existing menus,     *
	* should the menu be changed, I have to do  *
	* this in a really awkward and retarded way *
	********************************************/

	if(m_info.hSubMenu != 0)
	{
		RemoveMenu(m_parent->m_handle, (UINT)this, MF_BYCOMMAND);
		m_info.hSubMenu = (menu != 0 ? menu->GetHandle() : 0);
		InsertMenuItemW(m_parent->m_handle, m_position, true, &m_info);
	}
	else
	{
		m_info.hSubMenu = (menu != 0 ? menu->GetHandle() : 0);
		UpdateInfo();
	}
}

void MenuItem::SetText(const wchar_t *text)
{
	if(m_info.dwTypeData != 0)
		free(m_info.dwTypeData);

	m_info.dwTypeData = _wcsdup(text);
	m_info.cch = wcslen(text) + 1;

	UpdateInfo();
}

void MenuItem::SetImage(Bitmap *bitmap)
{
	m_info.hbmpItem = (HBITMAP)bitmap->GetHandle();

	UpdateInfo();
}

void MenuItem::SetCheckedImage(Bitmap *bitmap)
{
	m_info.hbmpChecked = (HBITMAP)bitmap->GetHandle();

	UpdateInfo();
}

void MenuItem::SetUncheckedImage(Bitmap *bitmap)
{
	m_info.hbmpUnchecked = (HBITMAP)bitmap->GetHandle();

	UpdateInfo();
}

void MenuItem::SetChecked(bool checked)
{
	m_info.fState = (checked ? (m_info.fState | MF_CHECKED) : (m_info.fState & ~MF_CHECKED));
	
	UpdateInfo();
}

bool MenuItem::GetChecked()
{
	return (m_info.fState & MF_CHECKED) > 0;
}

void MenuItem::OnMouseClick(MouseButton button)
{

}

void MenuItem::UpdateInfo()
{
	if(m_parent != 0)
	{
		m_info.fMask = MIIM_SUBMENU | MIIM_DATA | MIIM_STRING | MIIM_FTYPE | MIIM_STRING | MIIM_BITMAP | MIIM_CHECKMARKS | MIIM_ID | MIIM_STATE;
		SetMenuItemInfoW(m_parent->m_handle, (UINT)this, false, &m_info);
	}
}