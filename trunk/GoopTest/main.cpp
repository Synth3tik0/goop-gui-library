#include <Goop.h>
#include <Windows.h>

using namespace Goop;

// Class overloading
class MyTextbox : public Textbox
{
public:
	MyTextbox(const wchar_t *text = 0, Base *parent = 0) : Textbox(text, parent) {}

	bool OnTextChanged(const wchar_t *text)
	{
		wprintf(TEXT("Changed text: %s\n"), text);
		return false;
	}
};

#ifdef _DEBUG
	int main()
#else
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
#endif
{
	// Window test
	Window window = Window(L"My title");
	window.SetPosition(Vector2D(10, 20));

	// Label test
	Label label = Label(TEXT("Sup bitches"));
	label.SetPosition(Vector2D(10, 50));
	label.SetSize(Vector2D(200, 20));
	label.SetParent(&window);

	// Font test
	Font myFont(TEXT("Comic Sans MS"), 38, (FontStyle)(Strikeout | Underline | Italic));
	label.SetFont(&myFont);

	// Button test
	Button button = Button(TEXT("I'm a real button"), &window);
	button.SetPosition(Vector2D(200, 150));
	button.SetSize(Vector2D(200, 30));

	// Radio button test
	Radio button1 = Radio(TEXT("My button!"), &window);
	button1.SetPosition(Vector2D(200, 70));
	button1.SetSize(Vector2D(100, 25));

	Radio button2 = Radio(TEXT("Also button!"), &window);
	button2.SetPosition(Vector2D(200, 90));
	button2.SetSize(Vector2D(100, 25));
	button2.SetChecked(true);

	// Menu test
	Menu menu = Menu();
	Menu *first = menu.AddMenu(TEXT("First"));
		first->AddMenuItem(TEXT("Button C:"));
		MenuItem *separator = first->AddSeparator();
		Menu *second = first->AddMenu(TEXT("Do something"));
			MenuItem *btnTest = second->AddMenuItem(TEXT("Button test"));
				btnTest->SetChecked(true);
				first->SetText(TEXT("Changed!"));
	
	window.SetMenu(&menu);

	// Bitmap test
	Bitmap bmp = Bitmap(TEXT("test.bmp"));
	btnTest->SetImages(&bmp, &bmp);

	// Textbox test
	MyTextbox box = MyTextbox(TEXT("Hello world"));
	box.SetPosition(Vector2D(20, 150));
	box.SetSize(Vector2D(100, 20));
	box.SetParent(&window);

	while(window.IsValid())
	{
		window.Update();
	}

	return 0;
}