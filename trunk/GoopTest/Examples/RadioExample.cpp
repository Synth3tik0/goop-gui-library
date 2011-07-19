#include "examples.h"
using namespace Goop;

const wchar_t *groupNames[] = 
{
	TEXT("Radio Group #1"),
	TEXT("Radio Group #2")
};

const wchar_t *radioNames[] = 
{
	TEXT("Radio Button Number 1"),
	TEXT("Radio Button Number 2"),
	TEXT("Radio Button Number 3"),
	TEXT("Radio Button Number 4"),
	TEXT("Radio Button Number 5"),
	TEXT("Radio Button Number 6"),
	TEXT("Radio Button Number 7"),
	TEXT("Radio Button Number 8")
};

class ExampleRadio : public Radio
{
public:
	ExampleRadio(const wchar_t *text, Base *parent) : Radio(text, parent) {}

	bool OnChecked()
	{
		g_outputBox->AppendText(m_parent->GetText());
		g_outputBox->AppendText(TEXT("->"));
		g_outputBox->AppendText(GetText());
		g_outputBox->AppendText(TEXT(" was selected!\r\n"));

		return false;
	}
};

void RadioExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Label Example tab\r\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Radio"));

	for(int g = 0; g < 2; g++)
	{
		Group *group = new Group(groupNames[g], tab);
		group->SetPosition(Vector2D(10 + (g * 282), 10));
		group->SetSize(Vector2D(272, 200));

		for(int r = 0; r < 8; r++)
		{
			ExampleRadio *radio = new ExampleRadio(radioNames[r], group);
			radio->SetBackgroundColor(255, 255, 255);
			radio->SetSize(Vector2D(250, 20));
			radio->SetPosition(Vector2D(10, 20 + (r * 22)));
		}
	}
}