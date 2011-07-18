#ifndef LABEL_H
#define LABEL_H

#include "Base.h"
namespace Goop
{
	class Label : public Base
	{
	public:
		GOOP_API Label(const wchar_t *text = L"", Base *parent = 0);
		GOOP_API ~Label();

	private:

	};
}

#endif