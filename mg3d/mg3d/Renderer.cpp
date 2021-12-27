#include "Renderer.h"
#include "Cfg.h"
#include "Shaders.h"
#include "Models.h"

#include "glfw3.h"
#include "Lighting.h"

static FrameBuffer* FBO = nullptr;
static FrameBuffer* DFBO = nullptr;
static GLuint DepthFBO = 0;
static GLuint DepthMap = 0;

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

	//scene.Draw(pCamera, shaders::BasicDepth, DFBO->GetID(), false);
	scene.Draw(pCamera, shaders::DefaultObjShadows, FBO->GetID());

	glDisable(GL_DEPTH_TEST);

	FBO->Unbind();
	
	if (pCamera->GetPosition().y < scene.WaterLevel())
	{
		shaders::DefaultObjShadows->SetInt("underwater", 1);
	}
	else
		shaders::DefaultObjShadows->SetInt("underwater", 0);

	shaders::Everything->SetFloat("scr_width", cfg::GetWindowWidth());
	shaders::Everything->SetFloat("scr_height", cfg::GetWindowHeight());
	
	//glFramebufferDrawBufferEXT();
	//PostProcess::Kernel(FBO->GetTexture());
	//PostProcess::BlackAndWhite(FBO->GetTexture());
	//PostProcess::NoEffects(FBO->GetTexture());
	PostProcess::Everything(FBO->GetTexture(), DFBO->GetTexture());
}

static void InitDepthBuffer()
{
	GLCall(glGenTextures(1, &DepthMap));
	GLCall(glBindTexture(GL_TEXTURE_2D, DepthMap));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, cfg::GetWindowWidth(), cfg::GetWindowHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

	// attach depth texture as FBO's depth buffer


	GLCall(glGenFramebuffers(1, &DepthFBO));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, DepthFBO));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthMap, 0));
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "framebufferul e prost.." << std::endl;
	}
		//std::cout << "framebufferul e prost.." << std::endl;
}

void Renderer::Init()
{
	FBO = new FrameBuffer;
	DFBO = new FrameBuffer;
	InitDepthBuffer();
	PostProcess::Init();
}
