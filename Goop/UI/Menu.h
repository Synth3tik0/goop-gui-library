#ifndef MENU_H
#define MENU_H

#include "Window.h"

namespace Goop
{
	class Menu;
	class Bitmap;

	class MenuItem
	{
		friend Menu;
	public:
		GOOP_API MenuItem(Menu *parent, const wchar_t *text = 0);
		
		GOOP_API void SetText(const wchar_t *text);
		GOOP_API const wchar_t *GetText();

		GOOP_API void SetChecked(bool checked);
		GOOP_API bool GetChecked();

		GOOP_API virtual bool OnTextChanged(const wchar_t *newText, const wchar_t *oldText);
		GOOP_API virtual bool OnMouseClick(MouseButton button);
	protected:
		GOOP_API MenuItem();
		wchar_t *m_text;
		Bitmap *m_bitmap;
		Menu *m_parent;
	};

	class Menu : public MenuItem
	{
		friend Window;
		friend MenuItem;
	public:
		GOOP_API Menu(Menu *parent = 0, const wchar_t *text = 0);
		GOOP_API static Menu *GetByHandle(HMENU handle);
		GOOP_API MenuItem *GetItemByIndex(int index);
		GOOP_API HMENU GetHandle();
	private:
		HMENU m_handle;
	};
}

#endif