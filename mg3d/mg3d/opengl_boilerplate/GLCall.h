#pragma once
#include <iostream>
#include <glew.h>


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x)  GLClearError();\
					x;\
					ASSERT(GLLogCall(#x, __FILE__, __LINE__));


static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error]:(0x" << std::hex << error << "): " << function << " " << file << " (line " << std::dec << line << ")" << std::endl;
		return false;
	}
	return true;
}
