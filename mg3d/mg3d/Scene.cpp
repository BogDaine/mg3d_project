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

void Scene::SetTerrain(const std::string& imagePath)
{
	m_Terrain = new Terrain(imagePath);
}

void Scene::SetTerrain(Terrain *terrain)
{
	m_Terrain = terrain;
}

void Scene::PushEntity(Entity *entity)
{
	m_Entities.push_back(entity);
}

void Scene::InitShadowMap()
{
	GLCall(glGenTextures(1, &m_DepthMap));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthMap));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, cfg::GetShadowWidth(), cfg::GetShadowHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
	
	// attach depth texture as FBO's depth buffer
	
	
	GLCall(glGenFramebuffers(1, &m_DepthMapFBO));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap, 0));
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
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
	auto normal_mat = glm::mat3(glm::transpose(glm::inverse(glm::mat4(1))));
	//TO DO: Make this a separate function
	m_PointLight1.position = glm::vec3(-2.0f, 100.0f, -1.0f);
	//m_PointLight1.position = pCamera->GetPosition();
	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 0.1f, far_plane = 500.0f;
	lightProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, near_plane, far_plane);
	lightView = glm::lookAt(m_PointLight1.position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	shaders::ShadowMapDepth->SetMat4("lightSpaceMatrix", lightSpaceMatrix);
	shader->SetMat4("lightSpaceMatrix", lightSpaceMatrix);
	glViewport(0, 0, cfg::GetShadowWidth(), cfg::GetShadowHeight());

	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);

	glClear(GL_DEPTH_BUFFER_BIT);

	shaders::ShadowMapDepth->Bind();

	if (m_Terrain)
	{
		shaders::ShadowMapDepth->SetMat4("model", glm::scale(glm::translate(glm::mat4(1.0), { -50, 3, -50 }), { 100, 0.1, 100 }));
		m_Terrain->Draw();
	}

	for (const auto& entity : m_Entities)
	{
		entity->Draw(shaders::ShadowMapDepth);
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, cfg::GetWindowWidth(), cfg::GetWindowHeight());
	//

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	shader->SetMat4("model", glm::mat4(1));
	shader->SetMat4("projection", pCamera->GetProjectionMatrix());
	shader->SetMat4("view", pCamera->GetViewMatrix());
	shader->SetInt("shadowMap", 8);
	glActiveTexture(GL_TEXTURE8);
	GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthMap));

	shader->SetMat3("NormalMatrix", normal_mat);
	shader->SetVec3("viewPos", pCamera->GetPosition());
	shader->SetLight(m_PointLight1);
	shader->SetVec3("lightPos", m_PointLight1.position);
	shader->SetFloat("material.shininess", 0.6 * 128);

	

	for (const auto& entity : m_Entities)
	{
		entity->Draw(shader);
	}
	if (m_Terrain)
	{
		shader->SetMat4("model", glm::scale(glm::translate(glm::mat4(1.0), { -50, 3, -50 }), { 100, 0.1, 100 }));
		m_Terrain->Draw();
	}
	
	if(m_Skybox) m_Skybox->Draw(pCamera);
	
	//also draw lights that need to be drawn;
		
}