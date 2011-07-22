#ifndef MENU_H
#define MENU_H

#include <Windows.h>
#include "../Utility.h"

namespace Goop
{
	class MenuItem;
	class Bitmap;

	class Menu
	{
		friend MenuItem;
	public:
		GOOP_API Menu(bool popup = false);
		GOOP_API ~Menu();

		static Menu *GetByHandle(HMENU handle);
		GOOP_API MenuItem *GetItemByIndex(int index);

		GOOP_API HMENU GetHandle();

		GOOP_API void AddItem(MenuItem *item);
		GOOP_API void ShowCheckmarks(bool show);
	protected:
		MENUINFO m_info;
		HMENU m_handle;
	};
	
	class MenuItem
	{
		friend Menu;
	public:
		GOOP_API MenuItem(const wchar_t *text);
		GOOP_API MenuItem(Bitmap *bitmap);
		GOOP_API ~MenuItem();

		GOOP_API virtual void SetMenu(Menu *menu);
		GOOP_API virtual void SetText(const wchar_t *text);
		GOOP_API virtual void SetImage(Bitmap *bitmap);
		GOOP_API virtual void SetCheckedImage(Bitmap *bitmap);
		GOOP_API virtual void SetUncheckedImage(Bitmap *bitmap);

		GOOP_API virtual bool GetChecked();
		GOOP_API virtual void SetChecked(bool checked);

		GOOP_API virtual void OnMouseClick(MouseButton button);

	protected:
		MENUITEMINFOW m_info;
		Menu *m_parent;

	private:
		int m_position;
		void InitializeInfo();
		void UpdateInfo();
	};
}

#endif