#include "Renderer.h"
#include "Cfg.h"
#include "Shaders.h"
#include "Models.h"

#include "glfw3.h"
#include "Lighting.h"

static FrameBuffer* FBO;

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawScene(Scene& scene, Camera* pCamera)
{
	FBO->Bind();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Clear();
	glEnable(GL_DEPTH_TEST);

	scene.Draw(pCamera, shaders::DefaultObj);

	glDisable(GL_DEPTH_TEST);

	//PostProcess::Kernel(FBO->GetTexture());
	//PostProcess::BlackAndWhite(FBO->GetTexture());
	FBO->Unbind();
	//glFramebufferDrawBufferEXT();
	PostProcess::NoEffects(FBO->GetTexture());
}

void Renderer::Init()
{
	FBO = new FrameBuffer;
	PostProcess::Init();
}
