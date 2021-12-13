#include "Submarine.h"


Submarine::Submarine(const glm::vec3& pos):
	VisibleEntity(pos)
{
	SetModel(models::Submarine1);
	Rotate(glm::radians(-90.0f), 0, glm::radians(90.0f));
	//because otherwise it's not a submarine
}

void Submarine::Draw(Shader* pCamera)
{
	this->VisibleEntity::Draw(pCamera);
}

void Submarine::Update()
{
	this->VisibleEntity::Update();
}
