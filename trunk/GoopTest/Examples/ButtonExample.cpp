#include "examples.h"
using namespace Goop;

Base *g_otherButton = 0;

class ExampleButton : public Button
{
public:
	ExampleButton(const wchar_t *text, Base *parent) : Button(text, parent) {}

	bool OnMouseClick(Vector2D position, MouseButton button)
	{
		g_outputBox->AppendText(GetText());
		g_outputBox->AppendText(TEXT(" was pressed!\n"));

		g_otherButton->SetEnabled(true);
		g_otherButton = this;
		SetEnabled(false);

		return false;
	}
};

void ButtonExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Button Example tab\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Button"));

	ExampleButton *btn = new ExampleButton(TEXT("Button #1"), tab);
	btn->SetPosition(Vector2D(10, 10));
	btn->SetSize(Vector2D(150, 25));

	ExampleButton *btn2 = new ExampleButton(TEXT("Button #2"), tab);
	btn2->SetPosition(Vector2D(10, 45));
	btn2->SetSize(Vector2D(150, 25));
	btn2->SetEnabled(false);

	g_otherButton = btn2;
}