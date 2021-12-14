#pragma once

#include "Shader.h"

namespace shaders
{
	extern Shader* DefaultObj;
	extern Shader* DefaultObjShadows;
	extern Shader* ShadowMapDepth;
	void InitShaders();
}