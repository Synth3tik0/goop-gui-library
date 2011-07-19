#include "Image.h"
#include "../Bitmap.h"

using namespace Goop;

Image::Image(Bitmap *bitmap, Base *parent) : m_bitmap(0)
{
	HINSTANCE instanceHandle = GetModuleHandle(0);
	m_handle = (HWND)CreateWindowExW(0, L"STATIC", L"", WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	SetBitmap(bitmap);
}

Image::~Image()
{

}

void Image::SetBitmap(Bitmap *bitmap)
{
	m_bitmap = bitmap;
	InvalidateRect(m_handle, 0, true);
}

Bitmap *Image::GetBitmap()
{
	return m_bitmap;
}

void Image::DrawBitmap()
{
	if(m_bitmap != 0) {
		Vector2D imageSize = GetSize();
		Vector2D bitmapSize = m_bitmap->GetSize();

		PAINTSTRUCT paintStruct;

		HDC device = BeginPaint(m_handle, &paintStruct);
		HDC memory = CreateCompatibleDC(device);

		SelectObject(memory, m_bitmap->GetHandle() );

		StretchBlt(device, 0, 0, imageSize.m_x, imageSize.m_y, memory, 0, 0, bitmapSize.m_x, bitmapSize.m_y, SRCCOPY );

		DeleteDC(memory);
		EndPaint(m_handle, &paintStruct);
	}
}

bool Image::OnPaint()
{
	DrawBitmap();
	return true;
}