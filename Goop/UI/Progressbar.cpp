#include "Progressbar.h"
#include <CommCtrl.h>

using namespace Goop;

Progressbar::Progressbar(Base *parent)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );

	m_handle = (HWND)CreateWindowExW(0, PROGRESS_CLASS, L"", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instanceHandle, 0);

	InitializeBase();
	m_defaultProcess = SetWindowLongPtr(m_handle, GWLP_WNDPROC, (LONG_PTR)Base::Process);

	SetParent(parent);
	Show();
}

Progressbar::~Progressbar()
{

}

void Progressbar::SetProgress(int progress)
{
	::SendMessageW(m_handle, PBM_SETPOS, (WPARAM)progress, 0);
}

void Progressbar::SetRelativeProgress(int progress)
{
	::SendMessageW(m_handle, PBM_DELTAPOS, (WPARAM)progress, 0);
}

void Progressbar::SetRange(Vector2D range)
{
	::SendMessageW(m_handle, PBM_SETRANGE, (WPARAM)0, MAKELONG(range.m_x, range.m_y));
}

int Progressbar::GetProgress()
{
	return ::SendMessageW(m_handle, PBM_GETPOS, 0, 0);
}

Vector2D Progressbar::GetRange()
{
	PBRANGE range;
	::SendMessageA(m_handle, PBM_GETRANGE, 0, (LPARAM)&range);

	return Vector2D(range.iLow, range.iHigh);
}

void Progressbar::SetBarStyle(ProgressStyle style)
{
	//RemoveStyle(PBS_SMOOTH | PBS_SMOOTHREVERSE | PBS_MARQUEE | PBS_VERTICAL);
	AddStyle(((style & Smooth) ? PBS_SMOOTH : 0) |
		     ((style & SmoothReverse) ? PBS_SMOOTHREVERSE : 0) |
			 ((style & Marquee) ? PBS_MARQUEE : 0) |
			 ((style & Vertical) ? PBS_VERTICAL : 0));
}