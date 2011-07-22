#ifndef BUTTON_H
#define BUTTON_H

#include "Base.h"
namespace Goop
{
	class Button : public Base
	{
	public:
		GOOP_API Button(const wchar_t *text = L"", Base *parent = 0);
		GOOP_API ~Button();

	private:

	};
}

#endif