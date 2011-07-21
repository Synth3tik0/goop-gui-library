#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "Base.h"
namespace Goop
{
	class MessageProxy;

	class Combobox : public Base
	{
	public:
		GOOP_API Combobox(Base *parent = 0);
		GOOP_API ~Combobox();

		GOOP_API virtual unsigned int GetCurrentSelection();
		GOOP_API virtual const wchar_t *GetOptionText(unsigned int id);

		GOOP_API virtual void AddItem(const wchar_t *item);

		GOOP_API virtual void OnSelectionChanged(unsigned int index);
		GOOP_API static LRESULT ListProcess(HWND hWindow, unsigned int uMsg, WPARAM wParam, LPARAM lParam);
	private:
	
	};
}


#endif