#include "Entity.h"

Entity::Entity(const glm::vec3& pos) :
	m_Pos(pos)
{
}

VisibleEntity::VisibleEntity(const glm::vec3& pos):
	Entity(pos),
	m_ModelMatrix(glm::translate(glm::mat4(1), pos))
{
}

VisibleEntity::VisibleEntity(Model* model, const glm::vec3& pos) :
	Entity(pos),
	m_ModelMatrix(glm::translate(glm::mat4(1), pos)),
	m_Model(model)
{
}
