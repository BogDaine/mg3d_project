#pragma once

#include "Scene.h"

#include <glew.h>
#include <glfw3.h>
#include "InputHandler.h"
#include <string>

void InitWindow(GLFWwindow* &, const std::string&);
void WindowLoop(GLFWwindow*, Scene&, Camera*);