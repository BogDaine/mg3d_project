#pragma once
#include "Maths.h"
#include "Model.h"

class Camera;

class Entity
{
protected:
	glm::vec3 m_Pos;
	glm::vec3 m_Rot;

public:

	Entity() = default;
	Entity(const glm::vec3&);

	virtual void Draw(Camera*) {}
	
	virtual void Update() {}
};

class VisibleEntity : public Entity
{
protected:

	Model* m_Model = nullptr;

	glm::mat4 m_ModelMatrix;
	glm::mat3 m_NormalMatrix;

public:

	VisibleEntity(const glm::vec3&);

	VisibleEntity(Model*, const glm::vec3&);

	virtual void Draw(Camera*) override {};

	virtual void Update() override;

};