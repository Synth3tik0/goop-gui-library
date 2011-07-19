#include "GLControl.h"
#include "../include/glew.h"
#include "../include/wglew.h"
#include <gl\GL.h>

using namespace Goop;

GLControl::GLControl(Base *parent) : m_dc(0), m_hrc(0)
{
	HINSTANCE instanceHandle = GetModuleHandle( NULL );
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC)Base::Process;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instanceHandle;
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = L"GoopGLControl";
	windowClass.hIconSm = 0;
	RegisterClassEx(&windowClass);

	DWORD ExStyle = NULL;

	m_handle = (HWND)CreateWindowEx(ExStyle, L"GoopGLControl", L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, parent->GetHandle(), 0, instanceHandle, 0);

	InitializeBase();
	SetParent(parent);

	m_dc = GetDC(m_handle);

	m_version[0] = 0;
	m_version[1] = 0;
}

GLControl::~GLControl()
{
	DestroyContext();
}

bool GLControl::CreateContext(int majorVersion, int minorVersion, int colorBits, int depthBits)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = colorBits;
	pfd.cDepthBits = depthBits;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(m_dc, &pfd);
	if(pixelFormat == 0)
		return false;

	if(!SetPixelFormat(m_dc, pixelFormat, &pfd))
		return false;

	HGLRC tempContext = wglCreateContext(m_dc);
	wglMakeCurrent(m_dc, tempContext);

	GLenum error = glewInit();
	if(error != GLEW_OK)
		return false;

	

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion, 
		WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
	};

	if(wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hrc = wglCreateContextAttribsARB(m_dc, 0, attributes);
		wglMakeCurrent(0, 0);
		wglDeleteContext(tempContext);
		wglMakeCurrent(m_dc, m_hrc);
	}
	else
	{
		m_hrc = tempContext;
	}

	glGetIntegerv(GL_MAJOR_VERSION, &m_version[0]);
	glGetIntegerv(GL_MINOR_VERSION, &m_version[1]);

	if(!m_hrc)
		return false;

	return true;
}

bool GLControl::DestroyContext()
{
	if(m_hrc != 0)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(m_hrc);
		m_hrc = 0;
	}

	return true;
}

Vector2D GLControl::GetVersion()
{
	return Vector2D(m_version[0], m_version[1]);
}

bool GLControl::OnPaint()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    
    glBegin(GL_TRIANGLES);

    glVertex3f(-1.0f, -0.5f, -4.0f);    // lower left vertex
    glVertex3f( 1.0f, -0.5f, -4.0f);    // lower right vertex
    glVertex3f( 0.0f,  0.5f, -4.0f);    // upper vertex

    glEnd();

	SwapBuffers(m_dc);
	return true;
}