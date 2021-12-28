#pragma once

#include "Shader.h"

namespace shaders
{
	extern Shader* DefaultObj;
	extern Shader* DefaultObjShadows;
	extern Shader* ShadowMapDepth;
	extern Shader* Shadow_Lab;
	extern Shader* BasicDepth;
	extern Shader* Water;

	extern Shader* Everything;
	void InitShaders();
}