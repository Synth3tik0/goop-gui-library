#ifndef IPADDRESSCONTROL_H
#define IPADDRESSCONTROL_H

#include "Base.h"
namespace Goop
{
	class MessageProxy;

	class IPAddressControl : public Base
	{
	public:
		GOOP_API IPAddressControl(Base *parent = 0);
		GOOP_API ~IPAddressControl();
	private:
		MessageProxy *m_proxy;
	};
}

#endif