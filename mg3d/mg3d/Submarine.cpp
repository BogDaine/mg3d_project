#include "Submarine.h"


Submarine::Submarine(const glm::vec3& pos):
	VisibleEntity(pos)
{
	SetModel(models::Submarine1);
}

void Submarine::Draw(Shader* pCamera)
{
	this->VisibleEntity::Draw(pCamera);
}

void Submarine::Update()
{
	this->VisibleEntity::Update();
}
