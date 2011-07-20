#include "Menu.h"
#include "../Bitmap.h"

using namespace Goop;

Menu::Menu(Menu *parent, const wchar_t *text) : MenuItem(parent, text), m_handle(0)
{
	m_parent = parent;

	MENUINFO menuInfo;
	menuInfo.cbSize = sizeof(MENUINFO);
	menuInfo.fMask = MIM_MENUDATA | MIM_STYLE;
	menuInfo.dwMenuData = (ULONG_PTR)this;
	menuInfo.dwStyle = MNS_NOTIFYBYPOS;

	if(m_parent == 0)
	{
		m_handle = ::CreateMenu();
	}
	else
	{
		m_handle = ::CreatePopupMenu();

		MENUITEMINFOW itemInfo;
		itemInfo.cbSize = sizeof(MENUITEMINFOW);
		itemInfo.hSubMenu = m_handle;
		itemInfo.fMask = MIIM_SUBMENU;

		SetMenuItemInfo(parent->m_handle, (UINT)this, false, &itemInfo);
	}

	SetMenuInfo(m_handle, &menuInfo);
}

HMENU Menu::GetHandle()
{
	return m_handle;
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