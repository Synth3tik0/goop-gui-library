#ifndef FONT_H
#define FONT_H	
#include <Windows.h>
#include "Utility.h"

namespace Goop
{
	typedef enum
	{
		None = 0,
		Bold = 1,
		Underline = 2,
		Italic = 4,
		Strikeout = 8
	} FontStyle;

	class Font
	{
	public:
		GOOP_API Font(const wchar_t *typeface = 0, int size = 14, FontStyle style = None);
		GOOP_API ~Font();

		GOOP_API static Font *GetDefault();

		GOOP_API const wchar_t *GetTypeface();
		GOOP_API int GetSize();
	private:
		friend class Base;
		wchar_t *m_typeface;
		int m_size;
		HFONT m_font;
	};
};

#endif