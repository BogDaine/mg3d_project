#pragma once
#include <glfw3.h>

class Camera;

static enum eInputMode
{
	CAMERA_FIRST_PERSON,
	MENU
};

class InputHandler
{
protected:

	GLFWwindow* m_BoundWindow;
	Camera* m_BoundCamera;
	
	bool key_pressed[255] = { false };

public:

	InputHandler(GLFWwindow*);

	void KeyEvent(int key, int scancode, int action, int mods);

	void MousePosEvent(double xpos, double ypos);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
};

namespace mgInput
{
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void MouseCallback(GLFWwindow* window, double xpos, double ypos);
}