#include "Tab.h"
#include <CommCtrl.h>

using namespace Goop;

Tab::Tab(const wchar_t *text, Base *parent)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );

	m_handle = (HWND)CreateWindowExW(0, L"STATIC", L"", 0, 1, 22, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);
	SetParent(parent);

	SetBackgroundColor(255, 255, 255);
}

Tab::~Tab()
{

}

void Tab::SetParent(Base *parent)
{
	Base::SetParent(parent);

	if(parent != 0)
	{
		Vector2D size = parent->GetSize();
		SetPosition(Vector2D(1, 22));
		SetSize(Vector2D(size.m_x - 4, size.m_y - 24));
	}
}

void Tab::OnSelected()
{
	
}

void Tab::OnDeselected()
{
	
}

bool Tab::OnPerformLayout()
{
	if(m_parent != 0)
	{
		Vector2D size = m_parent->GetSize();
		SetPosition(Vector2D(1, 22));
		SetSize(Vector2D(size.m_x - 4, size.m_y - 24));
	}

	return false;
}