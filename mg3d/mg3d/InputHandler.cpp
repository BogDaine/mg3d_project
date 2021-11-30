#include "InputHandler.h"
#include "Camera.h"

#include <glfw3.h>

#include <iostream>

InputHandler::InputHandler(GLFWwindow* window, Camera* camera):
	m_BoundWindow(window),
	m_BoundCamera(camera)
{

	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));
	SetInputMode(eInputMode::CAMERA_FIRST_PERSON);
	
}

void InputHandler::KeyEvent(int key, int scancode, int action, int mods)
{

	switch (action)
	{
	case GLFW_PRESS:
		key_pressed[key] = true;
		//std::cout << key << std::endl;

		if (key == GLFW_KEY_ESCAPE)
		{
			switch (m_InputMode)
			{
			case eInputMode::CAMERA_FIRST_PERSON:
				SetInputMode(eInputMode::MENU);
				break;
			case eInputMode::MENU:
				SetInputMode(eInputMode::CAMERA_FIRST_PERSON);
				m_BoundCamera->SetFirstMouseMove(true);
				break;
			}
		}

		break;
	case GLFW_RELEASE:
		key_pressed[key] = false;
		break;
	}

}

void InputHandler::MousePosEvent(double xpos, double ypos)
{
	if(m_InputMode == eInputMode::CAMERA_FIRST_PERSON)
		m_BoundCamera->MouseControl(xpos, ypos);
}

void InputHandler::SetInputMode(const int& mode)
{
	m_InputMode = mode;

	switch (mode)
	{
	case eInputMode::CAMERA_FIRST_PERSON:
		glfwSetInputMode(m_BoundWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	case eInputMode::MENU:
		glfwSetInputMode(m_BoundWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	}
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