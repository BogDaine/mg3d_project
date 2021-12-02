#include "Submarine.h"

static Model* SubmarineModel;

Submarine::Submarine(const glm::vec3& pos):
	VisibleEntity(pos)
{
}

void Submarine::Draw(Camera* pCamera)
{
	this->VisibleEntity::Draw(pCamera);
}

void Submarine::Update()
{
	this->VisibleEntity::Update();
}
