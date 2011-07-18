#ifndef WINDOW_H
#define WINDOW_H

#include "Base.h"

namespace Goop
{
	class Menu;

	class Window : public Base
	{
	public:
		GOOP_API Window(const wchar_t *title = L"", Vector2D size = Vector2D(800, 600));
		GOOP_API ~Window();

		GOOP_API void SetTitle(const wchar_t *title);
		GOOP_API const wchar_t *GetTitle();

		GOOP_API void Maximize();
		GOOP_API void Minimize();
		GOOP_API void Restore();

		GOOP_API virtual Menu *GetMenu();
		GOOP_API virtual void SetMenu(Menu *);
	private:
		Menu *m_menu;
	};
}

#endif