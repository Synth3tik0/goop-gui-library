#ifndef TAB_H
#define TAB_H

#include "TabContainer.h"
#include "Base.h"
namespace Goop
{

	class Tab : public Base
	{
		friend TabContainer;
	public:
		GOOP_API Tab(const wchar_t *text = L"", Base *parent = 0);
		GOOP_API ~Tab();

		GOOP_API virtual void SetParent(Base *parent);

		GOOP_API virtual void OnSelected();
		GOOP_API virtual void OnDeselected();
	private:
		int m_id;
	};
}

#endif