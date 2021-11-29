#pragma once

#include <glew.h>
#include <glfw3.h>

#include <string>

void InitWindow(GLFWwindow*&, const std::string&);
void WindowLoop(GLFWwindow*&);