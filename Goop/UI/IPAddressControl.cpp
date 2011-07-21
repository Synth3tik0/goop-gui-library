#include "IPAddressControl.h"
#include "../MessageProxy.h"
#include <CommCtrl.h>

using namespace Goop;

IPAddressControl::IPAddressControl(Base *parent)
{
	m_proxy = new MessageProxy(this);
	HINSTANCE instanceHandle = GetModuleHandle(0);

	m_handle = (HWND)CreateWindowExW(0, WC_IPADDRESS, L"", WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_proxy->m_handle, 0, instanceHandle, 0); 

	SetWindowLongPtr(m_handle, GWLP_USERDATA, (LONG_PTR)this);
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	Show();
}

IPAddressControl::~IPAddressControl()
{
	delete m_proxy;
}