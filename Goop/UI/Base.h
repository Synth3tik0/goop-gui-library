#ifndef BASE_H
#define BASE_H

#include <vector>
#include <Windows.h>
#include "../Utility.h"
#include "../Font.h"

namespace Goop
{
	class Base
	{
	public:
		GOOP_API virtual void Show();
		GOOP_API virtual void Hide();

		GOOP_API virtual void SetEnabled(bool enabled);
		GOOP_API virtual bool GetEnabled();

		GOOP_API virtual void SetParent(Base *parent);
		GOOP_API virtual void AddChild(Base *child);
		GOOP_API virtual void RemoveChild(Base *child);
		GOOP_API virtual Base *GetParent();
		GOOP_API virtual HWND GetHandle();
		GOOP_API virtual bool IsValid();

		GOOP_API virtual void SetFont(Font *font);
		GOOP_API virtual Font *GetFont();
		GOOP_API virtual void SetPosition(Vector2D position);
		GOOP_API virtual void SetSize(Vector2D size);
		GOOP_API virtual Vector2D GetPosition();
		GOOP_API virtual Vector2D GetSize();	
		GOOP_API virtual void SetText(const wchar_t *text);
		GOOP_API virtual const wchar_t *GetText();
		GOOP_API virtual void SetBackgroundColor(int r, int g, int b);

		GOOP_API virtual void SendKeyInput(wchar_t key);

		GOOP_API virtual void Update();
		GOOP_API virtual void Destroy();
		GOOP_API virtual void Redraw();

		GOOP_API virtual DWORD GetStyle();
		GOOP_API virtual void SetStyle(DWORD style);
		GOOP_API virtual void AddStyle(DWORD style);
		GOOP_API virtual void RemoveStyle(DWORD style);

		GOOP_API virtual bool CanMove(Vector2D &position);
		GOOP_API virtual bool CanResize(Vector2D &position);
		
		// Mouse events
		GOOP_API virtual bool OnMouseDown(Vector2D position, MouseButton button);
		GOOP_API virtual bool OnMouseUp(Vector2D position, MouseButton button);
		GOOP_API virtual bool OnMouseClick(Vector2D position, MouseButton button);
		GOOP_API virtual bool OnMouseMove(Vector2D position);

		// Keyboard events
		GOOP_API virtual bool OnKeyInput(wchar_t key);
		GOOP_API virtual bool OnKeyDown(wchar_t key);
		GOOP_API virtual bool OnKeyUp(wchar_t key);

		GOOP_API virtual bool OnMove(Vector2D position);
		GOOP_API virtual bool OnResize(Vector2D size);
		GOOP_API virtual bool OnTextChanged(const wchar_t *text);
		GOOP_API virtual bool OnCreate();
		GOOP_API virtual bool OnClose();
		GOOP_API virtual bool OnDestroy();
		GOOP_API virtual bool OnPaint();
		GOOP_API virtual bool OnFocus(Base *oldFocus);
		GOOP_API virtual bool OnBlur(Base *newFocus);
		GOOP_API virtual bool OnPerformLayout();

	protected:
		GOOP_API Base();
		GOOP_API ~Base();
		GOOP_API void InitializeBase();
		GOOP_API static LRESULT Process(HWND hWindow, unsigned int uMsg, WPARAM wParam, LPARAM lParam);

		wchar_t *m_text;
		HBRUSH m_background;
		LONG_PTR m_defaultProcess;
		std::vector<Base *> m_children;
		Base *m_parent;
		HWND m_handle;
		Font *m_font;
		Vector2D m_position;
		Vector2D m_size;
	};
}

#endif