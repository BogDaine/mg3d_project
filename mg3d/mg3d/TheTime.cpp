#include "TheTime.h"
#include <glfw3.h>

static double dt = 0;
static double lastTime = 0;

double TheTime::DetlaTime()
{
	return dt;
}

void TheTime::UpdateDeltaTime()
{
	double currentTime = glfwGetTime();
	dt = currentTime - lastTime;
	lastTime = currentTime;
}
