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
	


public:

	Submarine(const glm::vec3&);

	void ApplyDrag();

	void HandleInput(const eSubmarineControl&);

	void Draw(Shader*) override;

	void Update() override;
};