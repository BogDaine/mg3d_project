#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Submarine.h"
class Submarine;
class Camera;

static enum eInputMode
{
	CAMERA_FIRST_PERSON,
	MENU
};

class InputHandler
{
protected:

	GLFWwindow* m_BoundWindow = nullptr;
	Camera* m_BoundCamera = nullptr;
	Submarine* m_BoundSubmarine = nullptr;
	
	int m_InputMode = eInputMode::CAMERA_FIRST_PERSON;

	bool key_pressed[360] = { false };
	bool key_toggled[360] = { false };

public:

	InputHandler(GLFWwindow*, Camera*);

	void BindSubmarine(Submarine*);

	void HandleTheInput();

	void KeyEvent(int key, int scancode, int action, int mods);

	void MousePosEvent(double xpos, double ypos);

	void SetInputMode(const int& mode);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
};

namespace mgInput
{
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void MouseCallback(GLFWwindow* window, double xpos, double ypos);
}