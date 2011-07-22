#include "TreeView.h"
#include <CommCtrl.h>

using namespace Goop;

TreeView::TreeView(Base *parent)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );

	DWORD ExStyle = WS_EX_CLIENTEDGE;
	m_handle = (HWND)CreateWindowExW(ExStyle, WC_TREEVIEW, L"", TVS_HASLINES, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	Show();
}

TreeView::~TreeView()
{

}