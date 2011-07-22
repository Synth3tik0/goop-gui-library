#include "examples.h"
using namespace Goop;

void IPAddressControlExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created IPAddressControl Example tab\n"));

	Tab *tab = tabContainer->AddTab(TEXT("IPAddressControl"));

	IPAddressControl *control = new IPAddressControl(tab);
	control->SetPosition(Vector2D(320, 10));
	control->SetSize(Vector2D(150, 20));
}