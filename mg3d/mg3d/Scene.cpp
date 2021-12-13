#include "Scene.h"
#include "Entity.h"

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

void Scene::Update()
{
	for (const auto& entity : m_Entities)
	{
		entity->Update();
	}
}

void Scene::Draw(Camera* pCamera, Shader* shader)
{
	if(m_Skybox) m_Skybox->Draw(pCamera);

	auto normal_mat = glm::mat3(glm::transpose(glm::inverse(glm::mat4(1))));

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