#include "Menu.h"
#include "../Bitmap.h"

using namespace Goop;

Menu::Menu() : m_handle(0), m_parent(0), m_text(0)
{
	m_handle = ::CreateMenu();
	SetStyle(0);
}

Menu::Menu(Menu *parent, const wchar_t *text) : m_handle(0), m_parent(0), m_text(0)
{
	m_handle = ::CreatePopupMenu();
	m_parent = parent;
	SetStyle(0);

	if(text != 0)
		m_text = _wcsdup(text);
}

Menu::~Menu()
{
	while(m_childMenus.size() > 0)
	{
		delete m_childMenus[0];
	}

	while(m_childItems.size() > 0)
	{
		delete m_childItems[0];
	}

	
	if(m_parent != 0)
	{
		for(unsigned int i = 0; i < m_parent->m_childMenus.size(); i++)
		{
			if(m_parent->m_childMenus[i] == this)
			{
				m_parent->m_childMenus.erase(m_parent->m_childMenus.begin() + i);
				break;
			}
		}
		DeleteMenu(m_parent->m_handle, (UINT)m_handle, MF_BYCOMMAND);
		DestroyMenu(m_handle);
	}
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

Menu *Menu::AddMenu(const wchar_t *text)
{
	Menu *newMenu = new Menu(this, text);
	AppendMenuW(m_handle, MF_STRING | MF_POPUP, (UINT)newMenu->m_handle, text);
	newMenu->SetStyle(0);
	return newMenu;
}

MenuItem *Menu::AddMenuItem(const wchar_t *text)
{
	MenuItem *item = new MenuItem(this, text);
	MENUITEMINFOW info;
	info.cbSize = sizeof( MENUITEMINFOW );
	info.fMask = MIIM_DATA | MIIM_STRING | MIIM_FTYPE | MIIM_ID | MIIM_STATE;
	info.wID = (UINT)item;
	info.dwItemData = (DWORD)item;
	info.dwTypeData = (wchar_t *)text;
	info.cch = wcslen(text) + 1;
	info.fState = MFS_UNCHECKED;
	info.fType = MFT_STRING;

	InsertMenuItemW(m_handle, (UINT)item, false, &info);

	return item;
}

MenuItem *Menu::AddSeparator()
{
	MenuItem *item = new MenuItem(this);
	MENUITEMINFOW info;
	info.cbSize = sizeof( MENUITEMINFOW );
	info.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_ID | MIIM_STATE;
	info.wID = (UINT)item;
	info.dwItemData = (DWORD)item;
	info.fState = MFS_UNCHECKED;
	info.fType = MFT_SEPARATOR;

	::InsertMenuItemW(m_handle, (UINT)item, false, &info);

	return item;
}

void Menu::SetChecked(bool checked)
{
	::CheckMenuItem(m_parent->m_handle, (UINT)this, MF_BYCOMMAND | (checked ? MF_CHECKED : MF_UNCHECKED));
}

bool Menu::GetChecked()
{
	return (::GetMenuState(m_parent->m_handle, (UINT)this, MF_BYCOMMAND) & MF_CHECKED) > 0;
}

const wchar_t *Menu::GetText()
{
	return m_text;
}

void Menu::SetText(const wchar_t *text)
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
	::SetMenuItemInfo(m_parent->m_handle, (UINT)m_handle, false, &info);
}

void Menu::SetImages(Bitmap *checked, Bitmap *unchecked)
{
	if(m_parent == 0)
		return;

	MENUITEMINFOW info;
	info.cbSize = sizeof(MENUITEMINFOW);
	info.fMask = MIIM_CHECKMARKS;	
	info.hbmpChecked = (HBITMAP)checked->GetHandle();
	info.hbmpUnchecked = (HBITMAP)unchecked->GetHandle();

	SetMenuItemInfo(m_parent->m_handle, (UINT)this, false, &info);
}

void Menu::SetStyle(DWORD style)
{
	MENUINFO info;
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_MENUDATA | MIM_STYLE;
	info.dwStyle = MNS_NOTIFYBYPOS | style;
	info.dwMenuData = (ULONG_PTR)this;
	::SetMenuInfo(m_handle, &info );
}

DWORD Menu::GetStyle()
{
	MENUINFO info;
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_STYLE;
	::GetMenuInfo(m_handle, &info);

	return info.dwStyle;
}

bool Menu::OnTextChanged(const wchar_t *newText,const wchar_t *oldText)
{

	return false;
}