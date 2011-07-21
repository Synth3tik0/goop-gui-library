#include "examples.h"
using namespace Goop;

class ExampleCombo : public Combobox
{
public:
	ExampleCombo(Base *parent) : Combobox(parent) {}

	void OnSelectionChanged(unsigned int id)
	{
		g_outputBox->AppendText(TEXT("Combobox selected "));
		g_outputBox->AppendText(GetOptionText(id));
		g_outputBox->AppendText(TEXT("\r\n"));
	}
};

void ComboboxExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Combobox Example tab\r\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Combobox"));

	ExampleCombo *box = new ExampleCombo(tab);
	box->SetSize(Vector2D(200, 22));
	box->SetPosition(Vector2D(10, 10));

	box->AddItem(TEXT("Option #1"));
	box->AddItem(TEXT("Option #2"));
	box->AddItem(TEXT("Option #3"));
}