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

	//TO DO: DELETE THIS

	auto normal_mat = glm::mat3(glm::transpose(glm::inverse(glm::mat4(1))));

	Light myLight = lights::WHITE;
	myLight.position = glm::vec3(sin(glfwGetTime()) * 24, 0.01f, cos(glfwGetTime()) * 24);

	shaders::DefaultObj->SetMat4("model", glm::mat4(1));
	shaders::DefaultObj->SetMat4("projection", glm::perspective(45.0f, float(cfg::GetWindowWidth()) / float(cfg::GetWindowHeight()), 0.01f, 100.0f));
	shaders::DefaultObj->SetMat4("view", pCamera->GetViewMatrix());


	shaders::DefaultObj->SetMat3("NormalMatrix", normal_mat);
	shaders::DefaultObj->SetVec3("viewPos", pCamera->GetPosition());
	shaders::DefaultObj->SetLight(myLight);
	shaders::DefaultObj->SetVec3("light.position", myLight.position);
	shaders::DefaultObj->SetVec3("light.ambient", myLight.ambient);
	shaders::DefaultObj->SetVec3("light.diffuse", myLight.diffuse);
	shaders::DefaultObj->SetVec3("light.specular", myLight.specular);
	
	shaders::DefaultObj->SetFloat("material.shininess", 0.6 * 128);

	models::Submarine1->Draw(*shaders::DefaultObj);
	scene.Draw(pCamera);

	glDisable(GL_DEPTH_TEST);

	PostProcess::Kernel(FBO->GetTexture());
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
