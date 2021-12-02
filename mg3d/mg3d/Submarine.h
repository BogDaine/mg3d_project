#pragma once

#include "Entity.h"

class Submarine :public VisibleEntity
{
protected:

public:

	Submarine(const glm::vec3&);

	void Draw(Camera*) override;

	void Update() override;
};