#include "Entity.h"

Entity::Entity(const glm::vec3& pos) :
	m_Pos(pos)
{
}

void Entity::SetScale(const float&, const float&, const float&)
{
}

void Entity::SetScale(const glm::vec3&)
{
}

void Entity::Scale(const float& x, const float& y, const float& z)
{
	m_Scale *= glm::vec3(x, y, z);
}

void Entity::Scale(const glm::vec3& val)
{
	m_Scale *= val;
}

void Entity::Rotate(const float& x, const float& y, const float& z)
{
	m_Rot += glm::vec3(x, y, z);
}

void Entity::Rotate(const glm::vec3& val)
{
	m_Rot += val;
}

void Entity::Translate(const float& x, const float& y, const float& z)
{
	m_Pos += glm::vec3(x, y, z);
}

void Entity::Translate(const glm::vec3& val)
{
	m_Pos += val;
}

VisibleEntity::VisibleEntity(const glm::vec3& pos):
	Entity(pos),
	m_ModelMatrix(glm::translate(glm::mat4(1), pos))
{
}

VisibleEntity::VisibleEntity(Model* model, const glm::vec3& pos) :
	Entity(pos),
	m_ModelMatrix(glm::translate(glm::mat4(1), pos)),
	m_NormalMatrix(glm::transpose(glm::inverse(m_ModelMatrix))),
	m_Model(model)
{
}



void VisibleEntity::Update()
{
	m_ModelMatrix = glm::translate(glm::mat4(1), m_Pos);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rot.x, { 1.0, 0.0, 0.0 });
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rot.y, { 0.0, 1.0, 0.0 });
	m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rot.z, { 0.0, 0.0, 1.0 });
	m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
	m_NormalMatrix= glm::transpose(glm::inverse(m_ModelMatrix));
}

void VisibleEntity::Draw(Shader *shader)
{
	shader->SetMat4("model", m_ModelMatrix);
	m_Model->Draw(shader);
}

void VisibleEntity::SetModel(Model *model)
{
	m_Model = model;
}
