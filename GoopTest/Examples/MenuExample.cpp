#include "examples.h"
using namespace Goop;

class ExampleMenuItem : public MenuItem
{
public:
	ExampleMenuItem(Menu *parent, const wchar_t *text) : MenuItem(parent, text) {}

	bool OnMouseClick(MouseButton button)
	{
		SetChecked(!GetChecked());
		return false;
	}
};

void MenuExample(Window *window)
{
	Menu *menu = new Menu();
	Menu *first = new Menu(menu, TEXT("Hello world!"));

	Menu *second = new Menu(first, TEXT("What's going on?"));
	MenuItem *item = new ExampleMenuItem(first, TEXT("Hello there!"));

	window->SetMenu(menu);
}