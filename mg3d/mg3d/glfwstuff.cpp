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
		//GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		//draw everything here, or in separate function(s) called here, probably

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
