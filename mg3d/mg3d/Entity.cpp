#include "Entity.h"

Entity::Entity(const glm::vec3& pos) :
	m_Pos(pos)
{
}

glm::vec3 Entity::Position() const
{
	return m_Pos;
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

void Entity::AddForce(const glm::vec3& val)
{
	m_Velocity += val;
}

void Entity::AddForce(const float& x, const float& y, const float& z)
{
	m_Velocity += glm::vec3(x, y, z);
}

void Entity::Translate(const glm::vec3& val)
{
	m_Pos += val;
}

void Entity::ExertVelocity()
{
	Translate(m_Velocity * (float) TheTime::DetlaTime());
}

glm::vec3 Entity::Forward() const
{
	return m_Forward;
}

glm::vec3 Entity::Up() const
{
	return m_Up;
}

glm::vec3 Entity::Right() const
{
	return m_Right;
}

void Entity::SetSceneRef(Scene *scene)
{
	m_SceneRef = scene;
}

void Entity::Update()
{
	// Calculate the new forward vector
	this->m_Forward.x = cos(glm::radians(-m_Yaw)) * cos(glm::radians(m_Pitch));
	this->m_Forward.y = sin(glm::radians(m_Pitch));
	this->m_Forward.z = sin(glm::radians(-m_Yaw)) * cos(glm::radians(m_Pitch));
	this->m_Forward = glm::normalize(this->m_Forward);
	// Also re-calculate the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Forward, { 0, 1, 0 }));//worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
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

VisibleEntity::VisibleEntity(Model *model, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale):
	Entity(pos),
	m_ModelMatrix(glm::translate(glm::mat4(1), pos)),
	m_NormalMatrix(glm::transpose(glm::inverse(m_ModelMatrix))),
	m_Model(model)
{
	m_Rot = rot;
	m_Scale = scale;
}



void VisibleEntity::Update()
{
	this->Entity::Update();

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
