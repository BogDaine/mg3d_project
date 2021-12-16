#include "Cfg.h"


namespace cfg
{
	unsigned int WindowWidth = WINDOW_WIDTH;
	unsigned int WindowHeight = WINDOW_HEIGHT;

	unsigned int ShadowWidth = 2048;
	unsigned int ShadowHeight = 2048;


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