#include "Renderer.h"

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
