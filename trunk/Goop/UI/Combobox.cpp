#include "Combobox.h"
#include <CommCtrl.h>
#include <WindowsX.h>
#include "../MessageProxy.h"

using namespace Goop;

const static HBRUSH g_whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

Combobox::Combobox(Base *parent)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );

	m_handle = (HWND)CreateWindowExW(0, WC_COMBOBOXW, L"", CBS_DROPDOWN | CBS_HASSTRINGS | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);
	
	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	
	COMBOBOXINFO info;
	info.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(m_handle, &info);

	// Set the GWLP_USERDATA variable to the original WNDPROC, and set the new WNDPROC to our overloaded one that sets the background.
	SetWindowLongPtr(info.hwndList, GWLP_USERDATA, (LONG_PTR)SetWindowLongPtr(info.hwndList, GWLP_WNDPROC, (LONG_PTR)Combobox::ListProcess));
}

Combobox::~Combobox()
{
	
}

void Combobox::AddItem(const wchar_t *item)
{
	::SendMessageW(m_handle, CB_ADDSTRING, 0, (LPARAM)item);
}

unsigned int Combobox::GetCurrentSelection()
{
	return ComboBox_GetCurSel(m_handle);
}

const wchar_t *Combobox::GetOptionText(unsigned int id)
{
	if(m_text != 0);
		free(m_text);

	m_text = (wchar_t *)malloc(sizeof(wchar_t) * (ComboBox_GetLBTextLen(m_handle, id) + 1));
	ComboBox_GetLBText(m_handle, id, m_text);

	return m_text;
}


void Combobox::OnSelectionChanged(unsigned int index)
{

}

LRESULT Combobox::ListProcess(HWND hWindow, unsigned int uMsg, WPARAM wParam, LPARAM lParam)
{
	WNDPROC defaultProcess = (WNDPROC)GetWindowLongPtr(hWindow, GWLP_USERDATA);

	switch(uMsg)
	{
	case WM_CTLCOLOREDIT:
		{
			return (INT_PTR)g_whiteBrush;
		}
	}

	return CallWindowProc(defaultProcess, hWindow, uMsg, wParam, lParam);
}