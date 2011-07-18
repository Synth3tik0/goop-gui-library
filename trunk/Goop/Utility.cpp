#include "Utility.h"

using namespace Goop;

Vector2D::Vector2D()
{
	m_x = 0;
	m_y = 0;
}

Vector2D::Vector2D(int x, int y)
{
	m_x = x;
	m_y = y;
}

int Vector2D::GetX()
{
	return m_x;
}

int Vector2D::GetY()
{
	return m_y;
}

int Vector2D::operator[](int index)
{
	if(index == 0)
		return m_x;

	return m_x;
}

int Vector2D::operator[](int index) const
{
	if(index == 0)
		return m_x;

	return m_y;
}