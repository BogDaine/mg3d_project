#pragma once
#include "Maths.h"
#include "Model.h"
#include "TheTime.h"

class Camera;
class Scene;

class Entity
{
protected:

	Scene* m_SceneRef = nullptr;

	glm::vec3 m_Pos;
	glm::vec3 m_Rot;
	glm::vec3 m_Scale = {1, 1, 1};

	glm::vec3 m_Forward;
	glm::vec3 m_Right;
	glm::vec3 m_Up;

	float m_Pitch = 0;
	float m_Yaw = 0;
	float m_Roll = 0;


	glm::vec3 m_Velocity;
	float m_ScaleFloat = 1;

public:

	Entity() = default;
	Entity(const glm::vec3&);

	glm::vec3 Position() const;

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

	glm::vec3 Forward() const;
	glm::vec3 Up() const;
	glm::vec3 Right() const;

	void SetSceneRef(Scene*);

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