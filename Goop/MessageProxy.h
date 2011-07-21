#ifndef MESSAGEPROXY_H
#define MESSAGEPROXY_H

#include <Windows.h>

namespace Goop
{
	class Base;

	class MessageProxy
	{
	public:
		HWND m_handle;

		MessageProxy(Base *client);
		~MessageProxy();
	private:
		static LRESULT Process(HWND hWindow, unsigned int uMsg, WPARAM wParam, LPARAM lParam);
		Base *m_client;
	};
}

#endif