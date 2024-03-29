#ifndef EXAMPLES_H
#define EXAMPLES_H
#include <Goop.h>

extern Goop::Textbox *g_outputBox;

void MenuExample(Goop::Window *window);

void ButtonExample(Goop::TabContainer *tab);
void LabelExample(Goop::TabContainer *tab);
void RadioExample(Goop::TabContainer *tab);
void ImageExample(Goop::TabContainer *tab);
void TextboxExample(Goop::TabContainer *tab);
void ComboboxExample(Goop::TabContainer *tab);
void ProgressExample(Goop::TabContainer *tab);
void IPAddressControlExample(Goop::TabContainer *tab);
void TreeViewExample(Goop::TabContainer *tab);

#endif