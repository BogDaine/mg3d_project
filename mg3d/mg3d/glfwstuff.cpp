#include "glfwstuff.h"
#include "Cfg.h"
#include "Renderer.h"

#include <iostream>

void InitWindow(GLFWwindow* (&window), const std::string& title)
{
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to initialize!" << std::endl;
		exit(-1);
	}

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), NULL, NULL);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW failed to initialize!" << std::endl;
		exit(-1);
	}
	
	glfwSwapInterval(1);

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glClearColor(0.5, 0.7, 0.4, 1.0));
	//TO DO: set up input callbacks

}

void WindowLoop(GLFWwindow*& window)
{
	while (!glfwWindowShouldClose(window))
	{
		Renderer::Clear();

		//draw everything here, or in separate function(s) called here, probably

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
