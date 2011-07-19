#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Base.h"
namespace Goop
{
	class MessageProxy;

	class Textbox : public Base
	{
	public:
		GOOP_API Textbox(const wchar_t *text = L"", Base *parent = 0);
		GOOP_API ~Textbox();

		GOOP_API virtual void SetMultiline(bool multiline);
		GOOP_API virtual bool GetMultiline();

		GOOP_API virtual void AppendText(const wchar_t *text);
	private:
		MessageProxy *m_proxy;
	};
}

#endif