#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "glfwstuff.h"

int main()
{
	GLFWwindow* window;
	InitWindow(window, "titlu imaginativ");
	WindowLoop(window);

    return 0;
}