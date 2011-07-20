#include "examples.h"
using namespace Goop;

static Menu *g_exampleMenu = 0;
static MenuItem *g_attachMenu = 0;

class ExampleMenuItem : public MenuItem
{
public:
	ExampleMenuItem(const wchar_t *text) : MenuItem(text) {}

	void OnMouseClick(MouseButton button)
	{
		if(GetChecked())
		{
			SetChecked(false);
			g_outputBox->AppendText(TEXT("Unchecked menu item\r\n"));
			g_attachMenu->SetMenu(0);
		}
		else
		{
			SetChecked(true);
			g_outputBox->AppendText(TEXT("Checked menu item\r\n"));
			g_attachMenu->SetMenu(g_exampleMenu);
		}
	}
};

void MenuExample(Window *window)
{
	g_outputBox->AppendText(TEXT("Created Menu Example\r\n"));

	Bitmap *bmp = new Bitmap(TEXT("goop.bmp"));

	MenuItem *bitmapExample = new MenuItem(bmp);
	bitmapExample->SetText(TEXT("And bitmaps :)"));

	ExampleMenuItem *overloadExample = new ExampleMenuItem(TEXT("Check me!"));
	MenuItem *moveExample = new MenuItem(TEXT("Hello there!"));

	g_exampleMenu = new Menu(true);
		g_exampleMenu->AddItem(new MenuItem(TEXT("Submenus work aswell")));
		g_exampleMenu->AddItem(bitmapExample);

	Menu *firstMenu = new Menu(true);
		firstMenu->AddItem(overloadExample);
		firstMenu->AddItem(moveExample);

	MenuItem *first = new MenuItem(TEXT("First"));
		first->SetMenu(firstMenu);
	
	Menu *menu = new Menu();
		menu->AddItem(first);

	g_attachMenu = moveExample;

	window->SetMenu(menu);
}