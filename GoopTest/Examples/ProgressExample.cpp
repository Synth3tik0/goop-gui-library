#include "examples.h"
using namespace Goop;

class ExampleBar : public Progressbar
{
public:
	ExampleBar(Base *parent, float progress) : Progressbar(parent), m_progress(0.0f) 
	{
		SetProgress((int)progress);
		m_progress = progress;
	}

	bool OnUpdate()
	{
		if(GetProgress() >= 100)
			m_progress = 0.0f;

		m_progress += 0.01f;		

		SetProgress((int)m_progress);
		return false;
	}
private:
	float m_progress;
};

void ProgressExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Progressbar Example tab\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Progress Bar"));

	for(float i = 0.0f; i < 100.0f; i += 10.0f)
	{
		ExampleBar *bar = new ExampleBar(tab, i);
		bar->SetSize(Vector2D(300, 25));
		bar->SetPosition(Vector2D(10, 10 + int(i * 3.0f)));
	}
	
	ExampleBar *vert = new ExampleBar(tab, 0.0f);
	vert->SetPosition(Vector2D(320, 10));
	vert->SetSize(Vector2D(25, 295));
	vert->SetBarStyle(Vertical);
}
