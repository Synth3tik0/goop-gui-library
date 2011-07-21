#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "Base.h"
namespace Goop
{
	class MessageProxy;

	class BaseCombobox : public Base
	{
	protected:
		GOOP_API BaseCombobox(Base *parent = 0, DWORD style = 0);
		GOOP_API ~BaseCombobox();

	public:
		GOOP_API virtual unsigned int GetCurrentSelection();
		GOOP_API virtual const wchar_t *GetOptionText(unsigned int id);

		GOOP_API virtual void AddItem(const wchar_t *item);
		GOOP_API virtual void AddItems(unsigned int itemCount, ...);

		GOOP_API virtual void OnSelectionChanged(unsigned int index);
		GOOP_API static LRESULT ListProcess(HWND hWindow, unsigned int uMsg, WPARAM wParam, LPARAM lParam);	
	};

	class Combobox : public BaseCombobox
	{
	public:
		GOOP_API Combobox(Base *parent = 0);
	};

	class Listbox : public BaseCombobox
	{
	public:
		GOOP_API Listbox(Base *parent = 0);
	};

	class List : public BaseCombobox
	{
	public:
		GOOP_API List(Base *parent = 0);
	};
}


#endif