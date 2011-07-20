#include "Menu.h"

using namespace Goop;

Menu::Menu(bool popup)
{
	memset(&m_info, 0, sizeof(MENUITEMINFOW));
	m_info.cbSize = sizeof(MENUINFO);
	m_info.fMask = MIM_BACKGROUND | MIM_HELPID | MIM_MAXHEIGHT | MIM_MENUDATA | MIM_STYLE;

	if(popup)
		m_handle = ::CreatePopupMenu();
	else
		m_handle = ::CreateMenu();

	GetMenuInfo(m_handle, &m_info);

	m_info.dwStyle = MNS_NOTIFYBYPOS;
	m_info.dwMenuData = (ULONG_PTR)this;

	SetMenuInfo(m_handle, &m_info);
}

Menu::~Menu()
{
	DestroyMenu(m_handle);
}

Menu *Menu::GetByHandle(HMENU handle)
{
	MENUINFO info;
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_MENUDATA;
	GetMenuInfo(handle, &info);

	return (Menu *)info.dwMenuData;
}

MenuItem *Menu::GetItemByIndex(int index)
{
	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_DATA;
	GetMenuItemInfo(m_handle, index, true, &info );

	return (MenuItem *)info.dwItemData;
}

HMENU Menu::GetHandle()
{
	return m_handle;
}

void Menu::AddItem(MenuItem *item)
{
	item->m_position = InsertMenuItemW(m_handle, (UINT)item, false, &item->m_info);
	item->m_parent = this;
}

void Menu::ShowCheckmarks(bool show)
{
	m_info.dwStyle = (show ? m_info.dwStyle & ~MNS_NOCHECK : m_info.dwStyle | MNS_NOCHECK);
	SetMenuInfo(m_handle, &m_info);
}