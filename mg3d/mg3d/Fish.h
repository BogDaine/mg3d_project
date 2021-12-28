#pragma once
#include "Entity.h"

class Fish : public VisibleEntity
{
	float m_Speed = 0;
public:
	Fish(Model* model, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale, const float& speed, const glm::vec3& velocity);
	void Update();
	void CollisionCheck();
};