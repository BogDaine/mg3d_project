#include "Submarine.h"


Submarine::Submarine(const glm::vec3& pos):
	VisibleEntity(pos)
{
	SetModel(models::Submarine1);
	//Rotate(glm::radians(-90.0f), 0, glm::radians(90.0f));
	//because otherwise it's not a submarine
}
void Submarine::ApplyDrag()
{
	float V = glm::length(m_Velocity);		// speed
	if (V == 0)
		return;

	float r = 997.0f;						//Medium density
	float Cd = 1.0f;						//Drag coefficient
	float A = 0.0007f + (1-glm::abs(cos(glm::angle(glm::normalize(m_Forward), glm::normalize(m_Velocity))))) * 0.001;						//Area of contact
	float Drag = (Cd * A * r * V * V) / 2;

	//std::cout << "speed: " << V << std::endl;
	//std::cout << "Drag: " << Drag << std::endl;

	m_Velocity += -Drag * (float) TheTime::DetlaTime() * glm::normalize(m_Velocity) ;
}
//
void Submarine::HandleInput(const eSubmarineControl& command)
{
	glm::vec3 rotation = {0,0,0};
	float ForwardSpeed = (cos(glm::angle(glm::normalize(m_Forward), glm::normalize(m_Velocity)))) * glm::length(m_Velocity) * 0.25f;
	switch (command)
	{

	case eSubmarineControl::FORWARD:
		AddForce(m_Forward * (float)TheTime::DetlaTime());
		break;
	case eSubmarineControl::BACKWARD:
		AddForce( - m_Forward * (float)TheTime::DetlaTime());
		break;
	case eSubmarineControl::LEFT:
		m_Yaw += 30 * TheTime::DetlaTime() * ForwardSpeed;
		rotation.y += glm::radians(30 * TheTime::DetlaTime()) * ForwardSpeed;
		break;
	case eSubmarineControl::RIGHT:
		m_Yaw -= 30 * TheTime::DetlaTime() * ForwardSpeed;
		rotation.y -= glm::radians(30 * TheTime::DetlaTime()) * ForwardSpeed;
		break;
	case eSubmarineControl::UP:
		m_Pitch += 30 * TheTime::DetlaTime() * ForwardSpeed;
		rotation.z += glm::radians(30 * TheTime::DetlaTime()) * ForwardSpeed;
		break;
	case eSubmarineControl::DOWN:
		m_Pitch -= 30 * TheTime::DetlaTime() * ForwardSpeed;
		rotation.z -= glm::radians(30 * TheTime::DetlaTime()) * ForwardSpeed;
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

	
	//std::cout << "speed: " << glm::length(m_Velocity) << std::endl;
	float speed = glm::length(m_Velocity);
	if (speed != 0)
	{
		auto newVel = glm::normalize(glm::normalize(m_Velocity) + m_Forward) * speed;
		m_Velocity = newVel;
	}

	ApplyDrag();
	ExertVelocity();
	this->VisibleEntity::Update();
	//Rotate(m_Pitch, 0, m_Yaw);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(-90.0f), { 1,0,0 });
	//m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(180.0f), { 0,1,0 });
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(90.0f), { 0,0,1 });
}
