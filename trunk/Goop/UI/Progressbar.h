#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "Base.h"
namespace Goop
{
	class Progressbar : public Base
	{
	public:
		GOOP_API Progressbar(Base *parent = 0);
		GOOP_API ~Progressbar();

		GOOP_API virtual void SetProgress(int progress);
		GOOP_API virtual void SetRelativeProgress(int progress);
		GOOP_API virtual void SetRange(Vector2D range);

		GOOP_API virtual int GetProgress();
		GOOP_API virtual Vector2D GetRange();

		GOOP_API virtual void SetBarStyle(ProgressStyle style);
	private:

	};
}

#endif