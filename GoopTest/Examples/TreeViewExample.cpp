#include "examples.h"
using namespace Goop;

void TreeViewExample(TabContainer *tabContainer)
{
	g_outputBox->AppendText(TEXT("Created Tree View example tab\n"));

	Tab *tab = tabContainer->AddTab(TEXT("Tree View"));

	TreeView *treeView = new TreeView(tab);
	treeView->SetPosition(Vector2D(10, 10));
	treeView->SetSize(Vector2D(200, 200));
}