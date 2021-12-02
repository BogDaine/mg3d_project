#include "Scene.h"
#include "Entity.h"

Scene::Scene()
{
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

void Scene::Update()
{
	for (const auto& entity : m_Entities)
	{
		entity->Update();
	}
}

void Scene::Draw(Camera* pCamera)
{
	if(m_Skybox) m_Skybox->Draw(pCamera);

	for (const auto& entity : m_Entities)
	{
		entity->Draw(pCamera);
	}

	//also draw lights that need to be drawn;
		
}