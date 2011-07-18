#ifndef GROUP_H
#define GROUP_H

#include "Base.h"
namespace Goop
{
	class Group : public Base
	{
	public:
		GOOP_API Group(const wchar_t *text = L"", Base *parent = 0);
		GOOP_API ~Group();

	private:

	};
}

#endif