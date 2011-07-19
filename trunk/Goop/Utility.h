#ifndef UTILITY_H
#define UTILITY_H

#define GOOP_API __declspec(dllexport)

namespace Goop
{
	const static char VERSION[] = "Goop 0.1";

	typedef enum
	{
		Left,
		Right,
		Middle,
	} MouseButton;

	typedef enum
	{
		Minimize,
		Maximize,
		Close
	} WindowButton;

	class GOOP_API Vector2D
	{
	public:
		Vector2D();
		Vector2D(int x, int y);
		int GetX();
		int GetY();
		int m_x;
		int m_y;

		int operator[](int index);
		int operator[](int index) const;
	};
}
#endif