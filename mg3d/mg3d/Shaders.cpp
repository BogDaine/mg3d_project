#include "Shaders.h"

Shader* shaders::DefaultObj;
Shader* shaders::ShadowMapDepth;
Shader* shaders::DefaultObjShadows;
void shaders::InitShaders()
{
	shaders::DefaultObj = new Shader("..\\shaders\\obj_default_vert.shader", "..\\shaders\\obj_default_frag.shader");
	shaders::ShadowMapDepth = new Shader("..\\shaders\\shadow_map_depth_vert.shader", "..\\shaders\\shadow_map_depth_frag.shader");
	shaders::DefaultObjShadows = new Shader("..\\shaders\\obj_default_shadows_vert.shader", "..\\shaders\\obj_default_shadows_frag.shader");
}