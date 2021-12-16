#pragma once

#include "Entity.h"
#include "Models.h"

enum class eSubmarineControl
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Submarine :public VisibleEntity
{
protected:
	glm::vec3 m_Forward;
	glm::vec3 m_Right;
	glm::vec3 m_Up;

	float m_Pitch = 0;
	float m_Yaw = 0;
	float m_Roll = 0;


public:

	Submarine(const glm::vec3&);

	void HandleInput(const eSubmarineControl&);

	void Draw(Shader*) override;

	void Update() override;
};