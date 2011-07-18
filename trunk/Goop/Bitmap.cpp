#include "Bitmap.h"

using namespace Goop;

Bitmap::Bitmap(HINSTANCE resourceSource, wchar_t* resourceName) {
	m_handle = LoadImageW(resourceSource, resourceName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
}

Bitmap::Bitmap(HINSTANCE resourceSource, int resourceIdentifier) {
	m_handle = LoadImageW( resourceSource, MAKEINTRESOURCE(resourceIdentifier), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
}

Bitmap::Bitmap(wchar_t *path) {
	m_handle = LoadImageW(GetModuleHandle(NULL), path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

Bitmap::Bitmap(HBITMAP Bmp) {
	m_handle = Bmp;
}

HANDLE Bitmap::GetHandle() {
	return m_handle;
}

Bitmap::~Bitmap() {
	::DeleteObject(m_handle);
}

Vector2D Bitmap::GetSize() {
	BITMAP bitmap;
	::GetObjectW(m_handle, sizeof(BITMAP), &bitmap);
	return Vector2D(bitmap.bmWidth, bitmap.bmHeight);
}