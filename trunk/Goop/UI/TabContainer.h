#ifndef TABCONTAINER_H
#define TABCONTAINER_H

#include "Base.h"
namespace Goop
{
	class Tab;

	class TabContainer : public Base
	{
	public:
		GOOP_API TabContainer(Base *parent = 0);
		GOOP_API ~TabContainer();

		GOOP_API virtual Tab *AddTab(const wchar_t *text);
		GOOP_API virtual Tab *GetTabByID(int id);
		GOOP_API virtual Tab *GetSelectedTab();
	private:

	};
}

#endif