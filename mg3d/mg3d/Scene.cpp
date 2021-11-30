#include "Scene.h"

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

}

void Scene::Draw(Camera* pCamera)
{
	if(m_Skybox) m_Skybox->Draw(pCamera);
		
}