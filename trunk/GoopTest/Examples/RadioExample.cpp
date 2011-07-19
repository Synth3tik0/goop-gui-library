#include "examples.h"
using namespace Goop;

const wchar_t *groupNames[] = 
{
	TEXT("Radio Group #1"),
	TEXT("Radio Group #2"),
	TEXT("Checkbox Group")
};

const wchar_t *radioNames[] = 
{
	TEXT("Radio Button Number 1"),
	TEXT("Radio Button Number 2"),
	TEXT("Radio Button Number 3"),
	TEXT("Radio Button Number 4"),
	TEXT("Radio Button Number 5"),
};

const wchar_t *checkNames[] = 
{
	TEXT("Checkbox Button Number 1"),
	TEXT("Checkbox Button Number 2"),
	TEXT("Checkbox Button Number 3"),
	TEXT("Checkbox Button Number 4"),
	TEXT("Checkbox Button Number 5"),
	TEXT("Checkbox Button Number 6"),
	TEXT("Checkbox Button Number 7"),
	TEXT("Checkbox Button Number 8"),
	TEXT("Checkbox Button Number 9"),
	TEXT("Checkbox Button Number 10"),
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

class ExampleCheckbox : public Checkbox
{
public:
	ExampleCheckbox(const wchar_t *text, Base *parent) : Checkbox(text, parent) {}

	bool OnChecked()
	{
		g_outputBox->AppendText(GetText());
		g_outputBox->AppendText(TEXT(" was checked!\r\n"));

		return false;
	}

	bool OnUnchecked()
	{
		g_outputBox->AppendText(GetText());
		g_outputBox->AppendText(TEXT(" was UNchecked!\r\n"));

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
		group->SetSize(Vector2D(272, 150));

		for(int r = 0; r < 5; r++)
		{
			ExampleRadio *radio = new ExampleRadio(radioNames[r], group);
			radio->SetBackgroundColor(255, 255, 255);
			radio->SetSize(Vector2D(250, 20));
			radio->SetPosition(Vector2D(10, 20 + (r * 25)));
		}
	}

	Group *group = new Group(groupNames[2], tab);
	group->SetPosition(Vector2D(10, 165));
	group->SetSize(Vector2D(554, 160));

	for(int i = 0; i < 2; i++)
	{
		for(int c = 0; c < 5; c++)
		{
			ExampleCheckbox *check = new ExampleCheckbox(checkNames[i * 5 + c], group);
			check->SetBackgroundColor(255, 255, 255);
			check->SetSize(Vector2D(250, 20));
			check->SetPosition(Vector2D(10 + (282 * i), 20 + (c * 27)));
		}
	}
}