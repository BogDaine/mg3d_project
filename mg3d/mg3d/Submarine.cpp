#include "Submarine.h"


Submarine::Submarine(const glm::vec3& pos):
	VisibleEntity(pos)
{
	SetModel(models::Submarine1);
	//Rotate(glm::radians(-90.0f), 0, glm::radians(90.0f));
	//because otherwise it's not a submarine
}
//
void Submarine::HandleInput(const eSubmarineControl& command)
{
	glm::vec3 rotation = {0,0,0};
	switch (command)
	{

	case eSubmarineControl::FORWARD:
		AddForce(m_Forward * (float)TheTime::DetlaTime());
		break;
	case eSubmarineControl::BACKWARD:
		AddForce( - m_Forward * (float)TheTime::DetlaTime());
		break;
	case eSubmarineControl::LEFT:
		m_Yaw += 30 * TheTime::DetlaTime();
		rotation.y += glm::radians(30 * TheTime::DetlaTime());
		break;
	case eSubmarineControl::RIGHT:
		m_Yaw -= 30 * TheTime::DetlaTime();
		rotation.y -= glm::radians(30 * TheTime::DetlaTime());
		break;
	case eSubmarineControl::UP:
		m_Pitch += 30 * TheTime::DetlaTime();
		rotation.z += glm::radians(30 * TheTime::DetlaTime());
		break;
	case eSubmarineControl::DOWN:
		break;

	}
		Rotate(rotation);
}

void Submarine::Draw(Shader* pCamera)
{
	this->VisibleEntity::Draw(pCamera);
}

void Submarine::Update()
{
	// Calculate the new forward vector
	this->m_Forward.x = cos(glm::radians(-m_Yaw)) * cos(glm::radians(m_Pitch));
	this->m_Forward.y = sin(glm::radians(m_Pitch));
	this->m_Forward.z = sin(glm::radians(-m_Yaw)) * cos(glm::radians(m_Pitch));
	this->m_Forward = glm::normalize(this->m_Forward);
	// Also re-calculate the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Forward, { 0, 1, 0 }));//worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(m_Right, m_Forward));

	
	
	ExertVelocity();
	this->VisibleEntity::Update();
	//Rotate(m_Pitch, 0, m_Yaw);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(-90.0f), { 1,0,0 });
	//m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(180.0f), { 0,1,0 });
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(90.0f), { 0,0,1 });
}
