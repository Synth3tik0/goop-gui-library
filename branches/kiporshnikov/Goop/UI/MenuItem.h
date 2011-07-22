#ifndef MENUITEM_H
#define MENUITEM_H

namespace Goop
{
	class GOOP_API MenuItem
	{
		friend Menu;
	public:
		virtual bool OnMouseClick(short x, short y, MouseButton button);
	private:
		MenuItem();
		~MenuItem();
	};
}

#endif