#ifndef MENU_H
#define MENU_H

#include "Window.h"

namespace Goop
{
	class MenuItem;
	class Bitmap;

	class Menu
	{
		friend Window;
		friend MenuItem;
	public:
		GOOP_API Menu();
		GOOP_API ~Menu();

		GOOP_API static Menu *GetByHandle(HMENU menu);
		GOOP_API virtual MenuItem *GetItemByIndex(int index);

		GOOP_API virtual Menu *AddMenu(const wchar_t *text);
		GOOP_API virtual MenuItem *AddMenuItem(const wchar_t *text);
		GOOP_API virtual MenuItem *AddSeparator();

		GOOP_API virtual void SetChecked(bool checked);
		GOOP_API virtual bool GetChecked();

		GOOP_API virtual const wchar_t *GetText();
		GOOP_API virtual void SetText(const wchar_t *text);

		GOOP_API virtual void SetImages(Bitmap *checked, Bitmap *unchecked);

		GOOP_API virtual void SetStyle(DWORD style);
		GOOP_API virtual DWORD GetStyle();

		GOOP_API virtual bool OnTextChanged(const wchar_t *newText, const wchar_t *oldText);

	private:
		wchar_t *m_text;
		Menu *m_parent;
		Menu(Menu *parent, const wchar_t *text);
		HMENU m_handle;

		std::vector<MenuItem *>m_childItems;
		std::vector<Menu *>m_childMenus;
	};

	class  MenuItem
	{
		friend Menu;
	public:
		GOOP_API ~MenuItem();

		GOOP_API virtual void SetChecked(bool checked);
		GOOP_API virtual bool GetChecked();

		GOOP_API virtual const wchar_t *GetText();
		GOOP_API virtual void SetText(const wchar_t *text);

		GOOP_API virtual void SetImages(Bitmap *checked, Bitmap *unchecked);

		GOOP_API virtual void SetInfo(MENUITEMINFOW info);
		GOOP_API virtual MENUITEMINFOW GetInfo(DWORD mask);		

		GOOP_API virtual bool OnTextChanged(const wchar_t *newText,const wchar_t *oldText);
		GOOP_API virtual bool OnMouseClick(MouseButton button);

	private:
		MenuItem(Menu *parent, const wchar_t *text);
		MenuItem(Menu *parent);

		wchar_t *m_text;
		Menu *m_parent;
	};
}

#endif