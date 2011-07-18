#include "MessageProxy.h"
#include "UI\Base.h"

using namespace Goop;

MessageProxy::MessageProxy(Base *parent)
{
	HINSTANCE hInst = GetModuleHandle( NULL );
	m_handle = CreateWindowExW(0, L"STATIC", L"", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInst, 0);
	SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)MessageProxy::Process);
	SetWindowLongPtr(m_handle, GWLP_USERDATA, (LONG_PTR)this);

	m_parent = parent;
}

MessageProxy::~MessageProxy()
{
	DestroyWindow(m_handle);
}

LRESULT MessageProxy::Process(HWND window, unsigned int msg, WPARAM wparam, LPARAM lparam)
{
	MessageProxy *proxy = (MessageProxy *)GetWindowLongPtr(window, GWLP_USERDATA);
	switch(msg)
	{
	case WM_COMMAND:
		{
			if(HIWORD(wparam) == EN_CHANGE)
			{
				proxy->m_parent->OnTextChanged(proxy->m_parent->GetText());
			}
			return 0;
		}
	}
	return DefWindowProc(window, msg, wparam, lparam);
}