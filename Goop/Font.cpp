#include "Font.h"

using Goop::Font;
using Goop::FontStyle;

Font::Font(const wchar_t *typeface, int size, FontStyle style)
	: m_size(size), m_typeface(0)
{
	if(typeface != 0)
		m_typeface = _wcsdup(typeface);

	LOGFONT lf;
	GetObjectA(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	m_font = CreateFont(
		size, 
		lf.lfWidth, 
        lf.lfEscapement, 
		lf.lfOrientation, 
		((style & Bold) > 0) ? FW_BOLD : FW_NORMAL, 
        ((style & Italic) > 0) ? true : false, 
		((style & Underline) > 0) ? true : false, 
		((style & Strikeout) > 0) ? true : false, 
		lf.lfCharSet, 
        lf.lfOutPrecision, 
		lf.lfClipPrecision, 
		lf.lfQuality, 
        lf.lfPitchAndFamily, 
		(typeface != 0 ? typeface : lf.lfFaceName) );
	int err = GetLastError();
}

Font::~Font()
{
	free(m_typeface);
	DeleteObject(m_font);
}

Font *Font::GetDefault()
{
	static Font *font = new Font();
	return font;
}

const wchar_t *Font::GetTypeface()
{
	return m_typeface;
}

int Font::GetSize()
{
	return m_size;
}