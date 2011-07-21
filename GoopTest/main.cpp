#include "Examples\examples.h"
#include <Windows.h>
using namespace Goop;

Textbox *g_outputBox = 0;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	Window window = Window(TEXT("Goop Example Application"), Vector2D(600, 550));
	window.ShowButton((WindowButton)(Minimize | Maximize), false);

	Textbox textbox = Textbox(TEXT(""), &window);
	textbox.SetPosition(Vector2D(5, 375));
	textbox.SetMultiline(true);
	textbox.SetSize(Vector2D(574, 110));

	g_outputBox = &textbox;

	textbox.AppendText(TEXT("Started Goop control test\n"));

	TabContainer container = TabContainer(&window);
	container.SetPosition(Vector2D(5, 5));
	container.SetSize(Vector2D(576, 363));

	// Create Examples
	MenuExample(&window);
	ButtonExample(&container);
	LabelExample(&container);
	RadioExample(&container);
	ImageExample(&container);
	TextboxExample(&container);
	ComboboxExample(&container);
	ProgressExample(&container);
	IPAddressControlExample(&container);

	window.Show();

	while(window.IsValid())
	{
		window.Update();
	}

	return 0;
}