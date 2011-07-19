#include "examples.h"
using namespace Goop;

void ImageExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Image Example tab\r\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Image"));

	Bitmap *bmp = new Bitmap(TEXT("goop.bmp"));

	Image *image = new Image(bmp, tab);
	image->SetSize(Vector2D(400, 150));
	image->SetPosition(Vector2D(87, 50));
	
	Image *small1 = new Image(bmp, tab);
	small1->SetSize(Vector2D(200, 75));
	small1->SetPosition(Vector2D(87, 200));
	
	Image *small2 = new Image(bmp, tab);
	small2->SetSize(Vector2D(200, 75));
	small2->SetPosition(Vector2D(287, 200));

	Font *font = new Font(TEXT("Segoe UI"), 14, Italic);

	Label *label = new Label(TEXT("Thanks to iNova for the cool logo!"), tab);
	label->SetBackgroundColor(255, 255, 255);
	label->SetSize(Vector2D(170, 20));
	label->SetPosition(Vector2D(406, 323));
	label->SetFont(font);
}