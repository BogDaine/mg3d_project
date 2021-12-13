#pragma once

#include "Entity.h"
#include "Models.h"

class Submarine :public VisibleEntity
{
protected:

public:

	Submarine(const glm::vec3&);

	void Draw(Shader*) override;

	void Update() override;
};