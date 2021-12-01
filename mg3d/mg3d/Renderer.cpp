#include "Renderer.h"
#include "Cfg.h"

static FrameBuffer* FBO;

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawScene(Scene& scene, Camera*& pCamera)
{
	FBO->Bind();
	Clear();
	glEnable(GL_DEPTH_TEST);


	scene.Draw(pCamera);

	glDisable(GL_DEPTH_TEST);


	PostProcess::Kernel(FBO->GetTexture());
	PostProcess::BlackAndWhite(FBO->GetTexture());
	FBO->Unbind();
	PostProcess::NoEffects(FBO->GetTexture());
}

void Renderer::Init()
{
	FBO = new FrameBuffer;
	PostProcess::Init();
}
