#include "Shaders.h"

Shader* shaders::DefaultObj;

void shaders::InitShaders()
{
	shaders::DefaultObj = new Shader("..\\shaders\\obj_default_vert.shader", "..\\shaders\\obj_default_frag.shader");
}