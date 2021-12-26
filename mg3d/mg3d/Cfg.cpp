#include "Cfg.h"


namespace cfg
{
	unsigned int WindowWidth = WINDOW_WIDTH;
	unsigned int WindowHeight = WINDOW_HEIGHT;

	unsigned int ShadowWidth = 4000;
	unsigned int ShadowHeight = 4000;


	unsigned int GetWindowWidth()
	{
		return WindowWidth;
	}
	unsigned int GetWindowHeight()
	{
		return WindowHeight;
	}
	unsigned int GetShadowWidth()
	{
		return ShadowWidth;
	}
	unsigned int GetShadowHeight()
	{
		return ShadowHeight;
	}
}