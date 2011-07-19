#include "Window.h"
#include "Menu.h"

using namespace Goop;

Window::Window(const wchar_t *title, Vector2D size) : m_menu(0)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = (WNDPROC)Base::Process;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instanceHandle;
	windowClass.hIcon = NULL;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"GoopWindow";
	windowClass.hIconSm = NULL;
	RegisterClassEx( &windowClass );

	DWORD ExStyle = NULL;

	m_handle = (HWND)CreateWindowEx(ExStyle, L"GoopWindow", L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.m_x, size.m_y, NULL, NULL, instanceHandle, NULL);
	m_size = size;

	InitializeBase();

	SetTitle(title);
}

Window::~Window()
{
	Destroy();
}

void Window::SetTitle(const wchar_t *title)
{
	SetText(title);
}

const wchar_t *Window::GetTitle()
{
	return GetText();
}

void Window::Maximize()
{
	::ShowWindow(m_handle, SW_MAXIMIZE);
}

void Window::Minimize()
{
	::ShowWindow(m_handle, SW_MINIMIZE);
}

void Window::Restore()
{
	::ShowWindow(m_handle, SW_RESTORE);
}

Menu *Window::GetMenu()
{
	return m_menu;
}

void Window::SetMenu(Menu *menu)
{
	m_menu = menu;
	::SetMenu(m_handle, m_menu->m_handle);
}

void Window::ShowButton(WindowButton button, bool show)
{
	if(show)
	{
		if((button & ::Minimize) > 0) RemoveStyle(WS_MINIMIZEBOX);
		if((button & ::Maximize) > 0) RemoveStyle(WS_MAXIMIZEBOX);
		if((button & ::Close) > 0)    RemoveStyle(WS_SYSMENU);
	}	
	else
	{	
		if((button & ::Minimize) > 0) RemoveStyle(WS_MINIMIZEBOX);
		if((button & ::Maximize) > 0) RemoveStyle(WS_MAXIMIZEBOX);
		if((button & ::Close) > 0)	  RemoveStyle(WS_SYSMENU);
	}
}