#include "Renderer.h"

static FrameBuffer* FBO;

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawScene(Scene& scene, Camera*& pCamera)
{
	FBO->Bind();
	scene.Draw(pCamera);
	FBO->Unbind();
}

void Renderer::Init()
{
	FBO = new FrameBuffer;
}
