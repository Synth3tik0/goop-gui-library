#include "Examples\examples.h"
#include <Windows.h>
using namespace Goop;

Textbox *g_outputBox = 0;

#ifdef _DEBUG
	int main()
#else
	int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
#endif
{
	Window window = Window(TEXT("Goop Example Application"), Vector2D(600, 550));
	window.ShowButton((WindowButton)(Minimize | Maximize), false);

	Textbox textbox = Textbox(TEXT(""), &window);
	textbox.SetPosition(Vector2D(5, 375));
	textbox.SetSize(Vector2D(576, 130));

	g_outputBox = &textbox;

	textbox.AppendText(TEXT("Started Goop control test\r\n"));

	TabContainer container = TabContainer(&window);
	container.SetPosition(Vector2D(5, 5));
	container.SetSize(Vector2D(576, 363));

	// Create Examples
	ButtonExample(&container);
	LabelExample(&container);

	while(window.IsValid())
	{
		window.Update();
	}

	return 0;
}