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
	int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
#endif
{
	// Window test
	Window window = Window(L"My title");
	window.SetPosition(Vector2D(10, 20));
	window.ShowButton(::Minimize, false);

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

	// Radio group test
	Group group = Group(TEXT("My Radio Group"), &window);
	group.SetPosition(Vector2D(200, 30));
	group.SetSize(Vector2D(200, 100));

	// Radio button test
	Radio button1 = Radio(TEXT("My button!"), &group);
	button1.SetPosition(Vector2D(10, 30));
	button1.SetSize(Vector2D(100, 20));

	Radio button2 = Radio(TEXT("Also button!"), &group);
	button2.SetPosition(Vector2D(10, 50));
	button2.SetSize(Vector2D(100, 20));
	button2.SetChecked(true);

	Checkbox cbox = Checkbox(TEXT("Not a button :("), &group);
	cbox.SetPosition(Vector2D(10, 70));
	cbox.SetSize(Vector2D(100, 20));

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

	// Image test
	Image img = Image(&bmp, &window);
	img.SetPosition(Vector2D(300, 200));
	img.SetSize(Vector2D(500, 500));
	
	// Tab/TabContainer test
	TabContainer tab = TabContainer(&window);
	tab.SetPosition(Vector2D(10, 300));
	tab.SetSize(Vector2D(200, 200));
		Tab *tab1 = tab.AddTab(TEXT("Tab 1"));
			Button btn = Button(TEXT("Button in tab!"), tab1);
			btn.SetPosition(Vector2D(10, 10));
			btn.SetSize(Vector2D(150, 25));
		Tab *tab2 = tab.AddTab(TEXT("Tab 2"));

	while(window.IsValid())
	{
		window.Update();
	}

	return 0;
}