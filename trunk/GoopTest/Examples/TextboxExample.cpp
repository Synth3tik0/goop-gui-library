#include "examples.h"
using namespace Goop;

class ExampleTextbox;

ExampleTextbox *g_textBoxes[4];

class ExampleTextbox : public Textbox
{
public:
	ExampleTextbox(const wchar_t *text, Base *parent) : Textbox(text, parent) {}

	bool OnKeyInput(wchar_t key)
	{
		if(key == 13)
		{
			for(int i = 0; i < 4; i++)
			{
				if(g_textBoxes[i] != this)
				{
					g_textBoxes[i]->SetText(GetText());
				}
			}

			return true;
		}

		return false;
	}
};

void TextboxExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Textbox Example tab\r\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Textbox"));

	for(int i = 0; i < 4; i++)
	{
		ExampleTextbox *box = new ExampleTextbox(TEXT(""), tab);
		box->SetPosition(Vector2D(10, 10 + i * 25));
		box->SetSize(Vector2D(200, 20));

		g_textBoxes[i] = box;
	}
}