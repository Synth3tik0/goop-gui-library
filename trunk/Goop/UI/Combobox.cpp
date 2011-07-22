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
	
	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	
	COMBOBOXINFO info;
	info.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(m_handle, &info);

	// Set the GWLP_USERDATA variable to the original WNDPROC, and set the new WNDPROC to our overloaded one that sets the background.
	SetWindowLongPtr(info.hwndList, GWLP_USERDATA, (LONG_PTR)SetWindowLongPtr(info.hwndList, GWLP_WNDPROC, (LONG_PTR)BaseCombobox::ListProcess));
	Show();
}

BaseCombobox::~BaseCombobox()
{
	
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
	WNDPROC defaultProcess = (WNDPROC)GetWindowLongPtr(hWindow, GWLP_USERDATA);
	static const HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

	switch(uMsg)
	{
	case WM_CTLCOLOREDIT:
		{
			return (INT_PTR)whiteBrush;
		}
	}

	return CallWindowProc(defaultProcess, hWindow, uMsg, wParam, lParam);
}

Combobox::Combobox(Base *parent) : BaseCombobox(parent, CBS_DROPDOWN) {}
Listbox::Listbox(Base *parent) : BaseCombobox(parent, CBS_DROPDOWNLIST) {}
List::List(Base *parent) : BaseCombobox(parent, CBS_SIMPLE) {}