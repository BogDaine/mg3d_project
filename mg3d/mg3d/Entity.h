#pragma once
#include "Maths.h"
#include "Model.h"
#include "TheTime.h"

class Camera;

class Entity
{
protected:
	glm::vec3 m_Pos;
	glm::vec3 m_Rot;
	glm::vec3 m_Scale = {1, 1, 1};



	glm::vec3 m_Velocity;
	float m_ScaleFloat = 1;

public:

	Entity() = default;
	Entity(const glm::vec3&);

	void SetScale(const float&, const float&, const float&);
	void SetScale(const glm::vec3&);

	void Scale(const float&, const float&, const float&);
	void Scale(const glm::vec3&);


	void Rotate(const float&, const float&, const float&);
	void Rotate(const glm::vec3&);

	void Translate(const float&, const float&, const float&);
	void Translate(const glm::vec3&);

	void AddForce(const float&, const float&, const float&);
	void AddForce(const glm::vec3&);


	void ExertVelocity();

	virtual void Draw(Shader*) {}
	
	virtual void Update();
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