#include "InputHandler.h"
#include <glfw3.h>

#include <iostream>

InputHandler::InputHandler(GLFWwindow* window)
	:m_BoundWindow(window)
{

	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

	
}

void InputHandler::KeyEvent(int key, int scancode, int action, int mods)
{

	switch (action)
	{
	case GLFW_PRESS:
		key_pressed[key] = true;
		//std::cout << key << std::endl;
		break;
	case GLFW_RELEASE:
		key_pressed[key] = false;
		break;
	}

}

void InputHandler::MousePosEvent(double xpos, double ypos)
{
}

void mgInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputHandler* handler = reinterpret_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	if (handler)
		handler->KeyEvent(key, scancode, action, mods);
}

void mgInput::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputHandler* handler = reinterpret_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	if (handler)
		handler->MousePosEvent(xpos, ypos);
}