#ifndef BITMAP_H
#define BITMAP_H	
#include <Windows.h>
#include "Utility.h"

namespace Goop
{
	class Bitmap 
	{
	private:
		HANDLE	m_handle;
		int		m_width;
		int		m_height;
	public:
		GOOP_API Bitmap(HINSTANCE resourceSource, wchar_t* resourceName );
		GOOP_API Bitmap(HINSTANCE resourceSource, int resourceIdentifier );
		GOOP_API Bitmap(wchar_t* path);
		GOOP_API Bitmap(HBITMAP bitmap);
		GOOP_API ~Bitmap();

		GOOP_API HANDLE	 GetHandle();
		GOOP_API Vector2D GetSize();
	};
}

#endif