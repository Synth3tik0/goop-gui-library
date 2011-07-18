#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Base.h"
namespace Goop
{
	class MessageProxy;

	class Checkbox : public Base
	{
	public:
		GOOP_API Checkbox(const wchar_t *text = L"", Base *parent = 0);
		GOOP_API ~Checkbox();

		GOOP_API bool GetChecked();
		GOOP_API void SetChecked(bool checked);

		GOOP_API virtual bool OnChecked();
		GOOP_API virtual bool OnUnchecked();
	private:
		unsigned int m_id;
		MessageProxy *m_proxy;
	};
}

#endif