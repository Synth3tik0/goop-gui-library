#ifndef RADIO_H
#define RADIO_H

#include "Base.h"
namespace Goop
{
	class MessageProxy;

	class Radio : public Base
	{
	public:
		GOOP_API Radio(const wchar_t *text = L"", Base *parent = 0);
		GOOP_API ~Radio();

		GOOP_API bool GetChecked();
		GOOP_API void SetChecked(bool checked);
	private:
		unsigned int m_id;
		MessageProxy *m_proxy;
	};
}

#endif