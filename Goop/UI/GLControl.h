#ifndef GLCONTROL_H
#define GLCONTROL_H

#include "Base.h"
namespace Goop
{
	class GLControl : public Base
	{
	public:
		GOOP_API GLControl(Base *parent = 0);
		GOOP_API ~GLControl();

		GOOP_API virtual bool CreateContext(int majorVersion = 4, int minorVersion = 0, int colorBits = 32, int depthBits = 32);
		GOOP_API virtual bool DestroyContext();

		GOOP_API virtual Vector2D GetVersion();

		GOOP_API virtual bool OnPaint();
	private:
		int m_version[2];
		HDC m_dc;
		HGLRC m_hrc;
	};
}

#endif