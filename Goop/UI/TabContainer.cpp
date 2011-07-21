#include "TabContainer.h"
#include "Tab.h"
#include <CommCtrl.h>

using namespace Goop;

TabContainer::TabContainer(Base *parent)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );

	m_handle = (HWND)CreateWindowExW(0, WC_TABCONTROL, L"", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	Show();
}

TabContainer::~TabContainer()
{

}

Tab *TabContainer::AddTab(const wchar_t *text)
{
	Tab *tab = new Tab(text, this);

	TCITEMW item;
	item.pszText = _wcsdup(text);
	item.mask = TCIF_TEXT | TCIF_PARAM;
	item.lParam = (LPARAM)tab;
	tab->m_id = TabCtrl_InsertItem(m_handle, INT_MAX, (LPARAM)&item);
	if(tab->m_id == 0)
	{
		tab->Show();
		tab->OnSelected();
	}
	return tab;
}

Tab *TabContainer::GetTabByID(int id)
{
	TCITEMW item;
	item.mask = TCIF_PARAM;
	TabCtrl_GetItem(m_handle, id, &item);

	return (Tab *)item.lParam;
}

Tab *TabContainer::GetSelectedTab()
{
	return GetTabByID(TabCtrl_GetCurSel(m_handle));
}