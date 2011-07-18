#ifndef IMAGE_H
#define IMAGE_H

#include "Base.h"
namespace Goop
{
	class Bitmap;

	class Image : public Base
	{
	public:
		GOOP_API Image(Bitmap *bitmap, Base *parent = 0);
		GOOP_API ~Image();

		GOOP_API virtual void SetImage(Bitmap *bitmap);
		GOOP_API virtual Bitmap *GetImage();

		GOOP_API virtual bool OnPaint();
	private:
		GOOP_API void DrawBitmap();
		Bitmap *m_bitmap;
	};
}

#endif