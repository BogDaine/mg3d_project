#include "InputHandler.h"
#include "Camera.h"

#include "TheTime.h"

#include <glfw3.h>

#include <iostream>

InputHandler::InputHandler(GLFWwindow* window, Camera* camera):
	m_BoundWindow(window),
	m_BoundCamera(camera)
{

	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));
	SetInputMode(eInputMode::CAMERA_FIRST_PERSON);
	
}

void InputHandler::HandleTheInput()
{
	switch (m_InputMode)
	{
	case eInputMode::CAMERA_FIRST_PERSON:

		if (key_pressed[GLFW_KEY_W])
			m_BoundCamera->ProcessKeyboard(ECameraMovementType::FORWARD, TheTime::DetlaTime());

		if (key_pressed[GLFW_KEY_S])
			m_BoundCamera->ProcessKeyboard(ECameraMovementType::BACKWARD, TheTime::DetlaTime());

		if (key_pressed[GLFW_KEY_A])
			m_BoundCamera->ProcessKeyboard(ECameraMovementType::LEFT, TheTime::DetlaTime());

		if (key_pressed[GLFW_KEY_D])
			m_BoundCamera->ProcessKeyboard(ECameraMovementType::RIGHT, TheTime::DetlaTime());


		break;

	case	eInputMode::MENU:
		break;
	}
}

void InputHandler::KeyEvent(int key, int scancode, int action, int mods)
{

	switch (action)
	{
	case GLFW_PRESS:
		key_pressed[key] = true;

		switch (m_InputMode)
		{
		case eInputMode::CAMERA_FIRST_PERSON:
			
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				SetInputMode(eInputMode::MENU);
				break;
			}
			
			break;
		case eInputMode::MENU:

			switch (key)
			{
			case GLFW_KEY_ESCAPE:
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