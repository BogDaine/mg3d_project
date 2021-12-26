#include "Scene.h"
#include "Entity.h"
#include "Shaders.h"
#include "Cfg.h"
#include "Models.h"
#include "Utility.h"

Scene::Scene()
{
	m_PointLight1.position = { 12, 10, 15 };
}

bool Scene::HasTerrain() const
{
	return m_HasTerrain;
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

void Scene::SetupSeaStuff()
{
	constexpr float pi = glm::pi<float>();
	float N = 3, M = 3;
	float r = 50;
	
	std::vector<Vertex>* HeightMap;
	int imgWidth, imgHeight;
	HeightmapInfo(HeightMap, imgWidth, imgHeight);

	for (float n = 0; n < 40; n++)
	{

		

		float TerrainHeight;
		
		auto posX = util::random_float(0.0f, 1.0f) * imgWidth; 
		auto posZ = util::random_float(0.0f, 1.0f) * imgHeight;
		
		if ((int)posX < imgHeight && (int) posZ < imgWidth)
		{
			TerrainHeight = HeightMap->operator[]((int)posX* imgWidth + posZ).Position.y * m_TerrainScale.y;

			auto position = glm::vec3(
				(float)posX * m_TerrainScale.x / imgWidth + m_TerrainTranslation.x,
				TerrainHeight,
				(float)posZ * m_TerrainScale.z / imgHeight + m_TerrainTranslation.z
			);

			auto scaleX = util::random_float(0.05f, 0.1f);// * 0.2f;
			auto scaleY = util::random_float(0.05f, 0.1f);// * 0.2f;
			auto scaleZ = util::random_float(0.05f, 0.1f);// * 0.2f;

			auto rotX = util::random_float(0.0f, glm::radians(360.0f));
			auto rotY = util::random_float(0.0f, glm::radians(360.0f));
			auto rotZ = util::random_float(0.0f, glm::radians(360.0f));

			PushEntity(new VisibleEntity(models::Coral2,
				position,
				glm::vec3(glm::radians(-90.0f), 0.0f, rotZ),
				glm::vec3(scaleX, scaleY, scaleZ)));
		}
	}


	for (float n = 0; n < 40; n++)
	{



		float TerrainHeight;

		auto posX = util::random_float(0.0f, 1.0f) * imgWidth;
		auto posZ = util::random_float(0.0f, 1.0f) * imgHeight;

		if ((int)posX < imgHeight && (int)posZ < imgWidth)
		{
			TerrainHeight = HeightMap->operator[]((int)posX* imgWidth + posZ).Position.y * m_TerrainScale.y;

			auto position = glm::vec3(
				(float)posX * m_TerrainScale.x / imgWidth + m_TerrainTranslation.x,
				TerrainHeight,
				(float)posZ * m_TerrainScale.z / imgHeight + m_TerrainTranslation.z
			);

			auto scaleX = util::random_float(0.4f, 1.2f);// * 0.2f;
			auto scaleY = util::random_float(0.4f, 1.2f);// * 0.2f;
			auto scaleZ = util::random_float(0.4f, 1.2f);// * 0.2f;

			auto rotX = util::random_float(0.0f, glm::radians(360.0f));
			auto rotY = util::random_float(0.0f, glm::radians(360.0f));
			auto rotZ = util::random_float(0.0f, glm::radians(360.0f));

			PushEntity(new VisibleEntity(models::Coral1,
				position,
				glm::vec3(0.0f, rotY, 0.0f),
				glm::vec3(scaleX, scaleY, scaleZ)));
		}
	}


}

void Scene::SetTerrain(const std::string& imagePath)
{
	m_Terrain = new Terrain(imagePath);
	m_HasTerrain = true;
}

void Scene::SetTerrain(Terrain *terrain)
{
	m_Terrain = terrain;
	m_HasTerrain = true;
}

void Scene::HeightmapInfo(std::vector<Vertex>*& vertices, int& imgWidth, int& imgHeight)
{
	m_Terrain->HeightmapInfo(vertices, imgWidth, imgHeight);
}

void Scene::PushEntity(Entity *entity)
{
	entity->SetSceneRef(this);
	m_Entities.push_back(entity);
}

glm::mat4 Scene::TerrainModelMatrix()
{
	return glm::scale(
			glm::translate(
				glm::mat4(1.0), m_TerrainTranslation),
		m_TerrainScale);
}

glm::vec3 Scene::TerrainTranslation()
{
	return m_TerrainTranslation;
}

glm::vec3 Scene::TerrainScale()
{
	return m_TerrainScale;
	return glm::vec3();
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
	m_PointLight1.position = glm::vec3(1.0f, 45.0f, 1.0f);
	m_PointLight1.ambient = {0.3, 0.3, 0.5};
	//m_PointLight1.position = pCamera->GetPosition();
	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 0.3f, far_plane = 250.0f;
	lightProjection = glm::ortho(-60.0f, 60.0f, -60.0f, 60.0f, near_plane, far_plane);
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
		shaders::ShadowMapDepth->SetMat4("model", TerrainModelMatrix());
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

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	for (const auto& entity : m_Entities)
	{
		entity->Draw(shader);
	}
	if (m_Terrain)
	{
		shader->SetMat4("model", TerrainModelMatrix());
		m_Terrain->Draw();
	}
	
	if(m_Skybox) m_Skybox->Draw(pCamera);
	
	//also draw lights that need to be drawn;
		
}