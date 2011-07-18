#include "Window.h"
#include "Menu.h"

using namespace Goop;

Window::Window(const wchar_t *title, Vector2D size) : m_menu(0)
{
	HINSTANCE hInst = GetModuleHandle( NULL );
	WNDCLASSEX sWindowClass;
	sWindowClass.cbSize = sizeof(WNDCLASSEX);
	sWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	sWindowClass.lpfnWndProc = (WNDPROC)Base::Process;
	sWindowClass.cbClsExtra = 0;
	sWindowClass.cbWndExtra = 0;
	sWindowClass.hInstance = hInst;
	sWindowClass.hIcon = NULL;
	sWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	sWindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	sWindowClass.lpszMenuName = NULL;
	sWindowClass.lpszClassName = L"GoopWindow";
	sWindowClass.hIconSm = NULL;
	RegisterClassEx( &sWindowClass );

	DWORD ExStyle = NULL;

	m_handle = (HWND)CreateWindowEx(ExStyle, L"GoopWindow", L"", WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.m_x, size.m_y, NULL, NULL, hInst, NULL);
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