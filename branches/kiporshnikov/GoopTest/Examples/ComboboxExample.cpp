#include "examples.h"
using namespace Goop;

class ExampleCombo : public Combobox
{
public:
	ExampleCombo(Base *parent) : Combobox(parent) {}

	void OnSelectionChanged(unsigned int id)
	{
		g_outputBox->AppendText(3, TEXT("Combobox selected "), GetOptionText(id), TEXT("\n"));
	}
};

void ComboboxExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Combobox Example tab\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Combobox"));

	ExampleCombo *combo = new ExampleCombo(tab);
	combo->SetSize(Vector2D(200, 22));
	combo->SetPosition(Vector2D(10, 10));

	combo->AddItems(3, TEXT("Option #1"), TEXT("Option #2"), TEXT("Option #3"));

	Listbox *box = new Listbox(tab);
	box->SetSize(Vector2D(200, 22));
	box->SetPosition(Vector2D(10, 42));

	box->AddItems(3, TEXT("Option #1"), TEXT("Option #2"), TEXT("Option #3"));

	List *list = new List(tab);
	list->SetSize(Vector2D(200, 132));
	list->SetPosition(Vector2D(10, 74));

	list->AddItems(3, TEXT("Option #1"), TEXT("Option #2"), TEXT("Option #3"));
}