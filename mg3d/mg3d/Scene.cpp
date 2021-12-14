#include "Scene.h"
#include "Entity.h"
#include "Shaders.h"
#include "Cfg.h"

Scene::Scene()
{
	m_PointLight1.position = { 12, 10, 15 };
}

void Scene::SetSkybox(const GLuint& cubemap)
{
	delete(m_Skybox);
	m_Skybox = new Skybox(cubemap);
}

void Scene::SetSkybox(std::vector<std::string>& faces)
{
	delete(m_Skybox);
	m_Skybox = new Skybox(faces);
}

void Scene::PushEntity(Entity *entity)
{
	m_Entities.push_back(entity);
}

void Scene::InitShadowMap()
{
	glGenTextures(1, &m_DepthMap);
	glBindTexture(GL_TEXTURE_2D, m_DepthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, cfg::GetShadowWidth(), cfg::GetShadowHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	// attach depth texture as FBO's depth buffer
	
	
	glGenFramebuffers(1, &m_DepthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::Update()
{
	for (const auto& entity : m_Entities)
	{
		entity->Update();
	}
}

void Scene::Draw(Camera* pCamera, Shader* shader, const GLuint &FBO)
{
	if(m_Skybox) m_Skybox->Draw(pCamera);

	auto normal_mat = glm::mat3(glm::transpose(glm::inverse(glm::mat4(1))));
	//TO DO: Make this a separate function

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 0.1f, far_plane = 500.0f;
	lightProjection = glm::ortho(-60.0f, 60.0f, -60.0f, 60.0f, near_plane, far_plane);
	lightView = glm::lookAt(m_PointLight1.position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	shaders::ShadowMapDepth->SetMat4("lightSpaceMatrix", lightSpaceMatrix);

	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);

	for (const auto& entity : m_Entities)
	{
		entity->Draw(shaders::ShadowMapDepth);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	shader->SetMat4("model", glm::mat4(1));
	shader->SetMat4("projection", pCamera->GetProjectionMatrix());
	shader->SetMat4("view", pCamera->GetViewMatrix());


	shader->SetMat3("NormalMatrix", normal_mat);
	shader->SetVec3("viewPos", pCamera->GetPosition());
	shader->SetLight(m_PointLight1);
	shader->SetFloat("material.shininess", 0.6 * 128);

	for (const auto& entity : m_Entities)
	{
		entity->Draw(shader);
	}

	//also draw lights that need to be drawn;
		
}