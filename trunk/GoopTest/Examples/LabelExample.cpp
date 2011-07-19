#include "examples.h"
using namespace Goop;

void LabelExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Label Example tab\r\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Label"));

	int offset = 10;
	for(int i = 5; i < 50; i+= 5)
	{
		Font *fontLeft = new Font(TEXT("Comic Sans MS"), i, (FontStyle)(Underline | Italic));
		Font *fontRight = new Font(TEXT("Tahoma"), i, (FontStyle)(Strikeout | Bold));

		Label *left = new Label(TEXT("This is a label!"), tab);
		left->SetPosition(Vector2D(10, offset));
		left->SetSize(Vector2D(300, i));
		left->SetFont(fontLeft);
		left->SetBackgroundColor(255, 255, 255);

		Label *right = new Label(TEXT("So is this!"), tab);
		right->SetPosition(Vector2D(300, offset));
		right->SetSize(Vector2D(300, i));
		right->SetFont(fontRight);
		right->SetBackgroundColor(255, 255, 255);

		offset += i + 10;
	}	
}