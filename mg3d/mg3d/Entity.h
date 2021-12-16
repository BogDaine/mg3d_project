#pragma once
#include "Maths.h"
#include "Model.h"

class Camera;

class Entity
{
protected:
	glm::vec3 m_Pos;
	glm::vec3 m_Rot;
	glm::vec3 m_Scale;
	float m_ScaleFloat = 1;

public:

	Entity() = default;
	Entity(const glm::vec3&);

	void Rotate(const float&, const float&, const float&);
	void Rotate(const glm::vec3&);

	void Translate(const float&, const float&, const float&);
	void Translate(const glm::vec3&);


	virtual void Draw(Shader*) {}
	
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

	void SetModel(Model*);

	virtual void Draw(Shader*) override;

	virtual void Update() override;

};