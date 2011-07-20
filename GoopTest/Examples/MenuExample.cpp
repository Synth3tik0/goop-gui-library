#include "examples.h"
using namespace Goop;

class ExampleMenuItem : public MenuItem
{
public:
	ExampleMenuItem(Menu *parent, const wchar_t *text) : MenuItem(parent, text) {}

	bool OnMouseClick(MouseButton button)
	{
		if(GetChecked())
		{
			SetChecked(false);
			g_outputBox->AppendText(TEXT("Unchecked menu item\r\n"));
		}
		else
		{
			SetChecked(true);
			g_outputBox->AppendText(TEXT("Checked menu item\r\n"));
		}
		return false;
	}
};

void MenuExample(Window *window)
{
	g_outputBox->AppendText(TEXT("Created Menu Example\r\n"));

	Menu *menu = new Menu();
	Menu *first = new Menu(menu, TEXT("Hello world!"));

	Menu *second = new Menu(first, TEXT("What's going on?"));
	MenuItem *item = new ExampleMenuItem(first, TEXT("Hello there!"));

	window->SetMenu(menu);
}