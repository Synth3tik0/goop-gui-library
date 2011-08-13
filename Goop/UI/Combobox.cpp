#include "Combobox.h"
#include <CommCtrl.h>
#include <WindowsX.h>
#include "../MessageProxy.h"
#include <cstdarg>

using namespace Goop;

BaseCombobox::BaseCombobox(Base *parent, DWORD style)
{
	HINSTANCE instanceHandle = GetModuleHandle(0);

	m_handle = (HWND)CreateWindowExW(0, WC_COMBOBOXW, L"", style | CBS_HASSTRINGS, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);
	
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	Show();
}

BaseCombobox::~BaseCombobox()
{
	
}

void BaseCombobox::InitializeBase()
{
	Base::InitializeBase(); 
	COMBOBOXINFO info;
	info.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(m_handle, &info);

	SetWindowLongPtr(info.hwndList, GWLP_USERDATA, (LONG_PTR)&m_comboData);

	m_comboData.listProc = (LONG_PTR)SetWindowLongPtr(info.hwndList, GWLP_WNDPROC, (LONG_PTR)BaseCombobox::ListProcess);

	if(info.hwndCombo != info.hwndItem)
	{
		SetWindowLongPtr(info.hwndItem, GWLP_USERDATA, (LONG_PTR)&m_comboData);
		m_comboData.itemProc = (LONG_PTR)SetWindowLongPtr(info.hwndItem, GWLP_WNDPROC, (LONG_PTR)BaseCombobox::ItemProcess);
	}

	m_comboData.parent = this;	
}

void BaseCombobox::AddItem(const wchar_t *item)
{
	::SendMessageW(m_handle, CB_ADDSTRING, 0, (LPARAM)item);
	::SendMessageW(m_handle, CB_SETCURSEL, 0, 0);
}

void BaseCombobox::AddItems(unsigned int itemCount, ...)
{
	va_list args;
	va_start(args, itemCount);

	for(unsigned int i = 0; i < itemCount; i++)
		::SendMessageW(m_handle, CB_ADDSTRING, 0, va_arg(args, LPARAM));

	va_end(args);
	::SendMessageW(m_handle, CB_SETCURSEL, 0, 0);
}

unsigned int BaseCombobox::GetCurrentSelection()
{
	return ComboBox_GetCurSel(m_handle);
}

const wchar_t *BaseCombobox::GetOptionText(unsigned int id)
{
	if(m_text != 0)
		free(m_text);

	m_text = (wchar_t *)malloc(sizeof(wchar_t) * (ComboBox_GetLBTextLen(m_handle, id) + 1));
	ComboBox_GetLBText(m_handle, id, m_text);

	return m_text;
}


void BaseCombobox::OnSelectionChanged(unsigned int index)
{

}

LRESULT BaseCombobox::ListProcess(HWND hWindow, unsigned int uMsg, WPARAM wParam, LPARAM lParam)
{
	ComboData *data = (ComboData *)GetWindowLongPtr(hWindow, GWLP_USERDATA);
	static const HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

	switch(uMsg)
	{
	case WM_CTLCOLOREDIT:
		{
			return (INT_PTR)whiteBrush;
		}
	}

	return CallWindowProc((WNDPROC)data->listProc, hWindow, uMsg, wParam, lParam);
}

LRESULT BaseCombobox::ItemProcess(HWND hWindow, unsigned int uMsg, WPARAM wParam, LPARAM lParam)
{
	ComboData *data = (ComboData *)GetWindowLongPtr(hWindow, GWLP_USERDATA);
	switch(uMsg)
	{
	case WM_CHAR:
		{
			if(data->parent->OnKeyInput((wchar_t)wParam))
				return 0;

			break;
		}
	}

	return CallWindowProc((WNDPROC)data->itemProc, hWindow, uMsg, wParam, lParam);
}

Combobox::Combobox(Base *parent) : BaseCombobox(parent, CBS_DROPDOWN) { InitializeBase(); }
Listbox::Listbox(Base *parent) : BaseCombobox(parent, CBS_DROPDOWNLIST) { InitializeBase(); }
List::List(Base *parent) : BaseCombobox(parent, CBS_SIMPLE) { InitializeBase(); }