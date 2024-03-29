#include "Base.h"
#include "Menu.h"
#include "Checkbox.h"
#include "TabContainer.h"
#include "Combobox.h"
#include "Tab.h"
#include <CommCtrl.h>
#include <WindowsX.h>

using namespace Goop;

Base::Base() : m_created(0), m_background(0), m_font(0), m_text(0), m_position(0, 0), m_size(0, 0), m_handle(0), m_parent(0), m_defaultProcess(0)
{

}

Base::~Base()
{
	if(m_text != 0)
		free(m_text);

	::CloseWindow(m_handle);
}

void Base::InitializeBase()
{
	SetWindowLongPtr(m_handle, GWLP_USERDATA, (LONG_PTR)this);
	SetFont(Font::GetDefault());
}

void Base::Show()
{
	::ShowWindow(m_handle, SW_SHOW);
}

void Base::Hide()
{
	::ShowWindow(m_handle, SW_HIDE);
}

void Base::SetEnabled(bool enabled)
{
	::EnableWindow(m_handle, enabled);
}

bool Base::GetEnabled()
{
	return (bool)(::IsWindowEnabled(m_handle) == TRUE);
}

void Base::SetParent(Base *parent)
{
	if(parent == m_parent) return;

	if(m_parent != 0) 
	{ // If we already have a parent, let them know we're being adoted.
		m_parent->RemoveChild( this );
		m_parent = 0;
	}

	if(parent == 0) 
	{ // If we're being orphaned
		::SetParent(m_handle, 0);
		RemoveStyle(WS_CHILD);
	} 
	else 
	{ // If we're being adopted.
		AddStyle(WS_CHILD);
		RemoveStyle(WS_CAPTION);

		m_parent = parent;
		parent->AddChild( this );
		::SetParent(m_handle, parent->GetHandle());
	}
	
	if(m_parent != 0)
	{
		m_parent->Redraw();
	}
}

void Base::AddChild(Base *child)
{
	if(child->GetParent() != this)
	{
		child->SetParent(this);
	}
	else
	{
		m_children.push_back(child);
	}
}

void Base::RemoveChild(Base *child)
{
	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		if(m_children[i] == child)
		{
			m_children.erase(m_children.begin() + i);
			if(child->GetParent() == this)
			{
				child->SetParent(0);
			}
			break;
		}
	}
}

Base *Base::GetParent()
{
	return m_parent;
}

void Base::SetFont(Font *font)
{
	::SendMessage(m_handle, WM_SETFONT, (WPARAM)font->m_font, true);
	m_font = font;
}

Font *Base::GetFont()
{
	return m_font;
}

void Base::SetPosition(Vector2D position)
{
	m_position = position;
	SetWindowPos(m_handle, 0, position.m_x, position.m_y, 0, 0, SWP_NOSIZE);
}

void Base::SetSize(Vector2D size)
{
	m_size = size;
	SetWindowPos(m_handle, 0, 0, 0, size.m_x, size.m_y, SWP_NOMOVE);
}

Vector2D Base::GetPosition()
{
	return m_position;
}

Vector2D Base::GetSize()
{
	return m_size;
}

void Base::SetText(const wchar_t *text)
{
	::SetWindowText(m_handle, text);
}

const wchar_t *Base::GetText()
{
	if(m_text != 0)
		free(m_text);

	int length = ::GetWindowTextLengthW(m_handle);
		
	m_text = (wchar_t *)malloc(sizeof(wchar_t) * (length + 1));
	::GetWindowTextW(m_handle, m_text, length + 1);
	
	return m_text;
}

void Base::SetBackgroundColor(int r, int g, int b)
{
	if(m_background != 0)
		DeleteObject(m_background);

	m_background = CreateSolidBrush(RGB(r, g, b));
}

void Base::SendKeyInput(wchar_t key)
{
	::SendMessageW(m_handle, WM_CHAR, (WPARAM)key, 0);
}

HWND Base::GetHandle()
{
	return m_handle;
}

void Base::Update()
{
	if(!m_created)
	{
		OnCreate();
		m_created = true;
	}

	MSG msg;
	while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Update();
	}

	OnUpdate();
}

void Base::Destroy()
{
	if(m_handle != 0)
	{
		DestroyWindow(m_handle);
		m_handle = 0;
	}
}

void Base::Redraw()
{
	::InvalidateRect(m_handle, 0, true);
}

DWORD Base::GetStyle()
{
	return ::GetWindowLong(m_handle, GWL_STYLE);
}

void Base::SetStyle(DWORD style)
{
	::SetWindowLong(m_handle, GWL_STYLE, style);
}

void Base::AddStyle(DWORD style)
{
	SetStyle(GetStyle() | style);
}

void Base::RemoveStyle(DWORD style)
{
	SetStyle(GetStyle() & (~style));
}

bool Base::IsValid()
{
	return m_handle != 0;
}

bool Base::CanMove(Vector2D &position)
{
	return true;
}

bool Base::CanResize(Vector2D &size)
{
	return true;
}

bool Base::OnMouseMove(Vector2D position)
{
	return false;
}

bool Base::OnMouseDown(Vector2D position, MouseButton button)
{
	return false;
}

bool Base::OnMouseUp(Vector2D position, MouseButton button)
{
	return false;
}

bool Base::OnMouseClick(Vector2D position, MouseButton button)
{
	return false;
}

bool Base::OnKeyInput(wchar_t key)
{
	return false;
}

bool Base::OnKeyDown(wchar_t key)
{
	return false;
}

bool Base::OnKeyUp(wchar_t key)
{
	return false;
}

bool Base::OnMove(Vector2D position)
{
	return false;
}

bool Base::OnResize(Vector2D size)
{
	return false;
}

bool Base::OnTextChanged(const wchar_t *text)
{
	return false;
}

bool Base::OnCreate()
{
	return false;
}

bool Base::OnClose()
{
	Destroy();
	return true;
}

bool Base::OnUpdate()
{
	return false;
}

bool Base::OnDestroy()
{
	return false;
}

bool Base::OnPaint()
{
	return false;
}

bool Base::OnFocus(Base *oldFocus)
{
	return false;
}

bool Base::OnBlur(Base *newFocus)
{
	return false;
}

bool Base::OnPerformLayout()
{
	return false;
}

LRESULT Base::Process(HWND window, unsigned int msg, WPARAM wparam, LPARAM lparam)
{
	Base *element = (Base *)GetWindowLongPtr(window, GWLP_USERDATA);

	if(element != 0)
	{
		switch(msg)
		{
		case BM_SETCHECK:
			{
				if(wparam == BST_CHECKED)
					((Checkbox *)element)->OnChecked();
				else
					((Checkbox *)element)->OnUnchecked();

				break;
			}
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			{
				POINTS pos = MAKEPOINTS(lparam);
				MouseButton button = (msg == WM_LBUTTONDOWN) ? Left : ((msg == WM_RBUTTONDOWN) ? Right : Middle);

				if(element->OnMouseDown(Vector2D(pos.x, pos.y), button))
					return 0;

				break;
			}
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			{
				POINTS pos = MAKEPOINTS(lparam);
				MouseButton button = (msg == WM_LBUTTONUP) ? Left : ((msg == WM_RBUTTONUP) ? Right : Middle);

				element->OnMouseClick(Vector2D(pos.x, pos.y), button);

				if(element->OnMouseUp(Vector2D(pos.x, pos.y), button))
					return 0;

				break;
			}
		case WM_MENUCOMMAND:
			{
				Menu *menu = Menu::GetByHandle((HMENU)lparam);
				MenuItem *item = menu->GetItemByIndex(wparam);
				item->OnMouseClick(Left);
				
				break;
			}
		case WM_MOUSEMOVE:
			{
				POINTS pos = MAKEPOINTS(lparam);
				if(element->OnMouseMove(Vector2D(pos.x, pos.y)))
					return 0;

				break;
			}
		case WM_SETTEXT:
			{
				if(element->OnTextChanged((const wchar_t *)lparam))
					return 0;

				break;
			}
		case WM_PAINT:
			{
				if(element->OnPaint())
				{
					ValidateRect(element->m_handle, 0);
					return 0;
				}

				break;
			}
		case WM_CREATE:
			{
				if(element->OnCreate())
					return 0;

				break;
			}
		case WM_CLOSE:
			{
				if(element->OnClose())
					return 0;

				break;
			}
		case WM_DESTROY:
			{
				element->m_handle = 0;
				
				if(element->OnDestroy())
					return 0;

				break;
			}
		case WM_CTLCOLORSTATIC:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORSCROLLBAR:
			{
				Base *control = (Base *)GetWindowLongPtr((HWND)lparam, GWLP_USERDATA);
				if(control != 0 && control->m_background != 0)
					return (INT_PTR)control->m_background;

				break;
			}
		case WM_WINDOWPOSCHANGING:
			{
				WINDOWPOS* pos = (WINDOWPOS*)lparam;

				if((pos->flags & SWP_NOSIZE) == 0)
				{
					Vector2D position = Vector2D(pos->cx, pos->cy);
					if(!element->CanResize(position))
					{
						pos->flags |= SWP_NOSIZE;
					}
					pos->cx = position.m_x;
					pos->cy = position.m_y;
				}
			
				if((pos->flags & SWP_NOMOVE) == 0)
				{
					Vector2D position = Vector2D(pos->x, pos->y);
					if(!element->CanMove(position))
					{
						pos->flags |= SWP_NOMOVE;
					}
					pos->x = position.m_x;
					pos->y = position.m_y;
				}
				break;
			}
		case WM_WINDOWPOSCHANGED:
			{
				WINDOWPOS *pos = (WINDOWPOS *)lparam;
				element->m_position = Vector2D(pos->x, pos->y);
				element->m_size = Vector2D(pos->cx, pos->cy);

				if((pos->flags & SWP_NOMOVE) == 0)
				{
					element->OnMove(Vector2D(pos->x, pos->y));
				}

				if((pos->flags & SWP_NOSIZE) == 0)
				{
					element->OnResize(Vector2D(pos->cx, pos->cy));
					for(unsigned int i = 0; i < element->m_children.size(); i++)
						element->m_children[i]->OnPerformLayout();
				}

				break;
			}
		case WM_KILLFOCUS:
			{
				Base *newFocus = (Base *)GetWindowLongPtr((HWND)wparam, GWLP_USERDATA);
				if(element->OnBlur(newFocus))
					return 0;

				break;
			}
		case WM_SETFOCUS:
			{
				Base *oldFocus = (Base *)GetWindowLongPtr((HWND)wparam, GWLP_USERDATA);
				if(element->OnFocus(oldFocus))
					return 0;

				break;
			}
		case WM_CHAR:
			{
				if(element->OnKeyInput((wchar_t)wparam))
					return 0;

				break;
			}
		case WM_KEYDOWN:
			{
				if(element->OnKeyDown((wchar_t)wparam))
					return 0;

				break;
			}
		case WM_KEYUP:
			{
				if(element->OnKeyUp((wchar_t)wparam))
					return 0;

				break;
			}
		case WM_NOTIFY:
			{
				NMHDR info = *(NMHDR *)lparam;
				switch(info.code)
				{
				case TCN_SELCHANGING:
					{
						TabContainer *container = (TabContainer *)GetWindowLongPtr((HWND)info.hwndFrom, GWLP_USERDATA);
						
						Tab *current = container->GetSelectedTab();
						current->Hide();
						current->OnDeselected();

						break;
					}
				case TCN_SELCHANGE:
					{
						TabContainer *container = (TabContainer *)GetWindowLongPtr((HWND)info.hwndFrom, GWLP_USERDATA);
						
						Tab *current = container->GetSelectedTab();
						current->Show();
						current->OnSelected();

						break;
					}
				}
				break;
			}
		case WM_COMMAND:
			{

				switch(HIWORD(wparam))
				{
				case CBN_SELENDOK:
					{
						BaseCombobox *box = (BaseCombobox *)element;

						int selection = ComboBox_GetCurSel(box->GetHandle());
						box->OnSelectionChanged(selection);
						box->OnTextChanged(box->GetOptionText(selection));

						break;
					}
				case CBN_EDITCHANGE:
					{
						BaseCombobox *box = (BaseCombobox *)element;
						box->OnTextChanged(box->GetText());
						break;
					}
				default:
					{
						break;
					}
				}
				break;
			}
		default:
			{
				break;
			}
		}

		if(element->m_defaultProcess != 0)
		{
			return CallWindowProc((WNDPROC)element->m_defaultProcess, window, msg, wparam, lparam);
		}
	}
	
	return DefWindowProc(window, msg, wparam, lparam);
}