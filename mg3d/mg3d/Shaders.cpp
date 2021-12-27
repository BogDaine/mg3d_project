#include "Shaders.h"

Shader* shaders::DefaultObj;
Shader* shaders::ShadowMapDepth;
Shader* shaders::DefaultObjShadows;
Shader* shaders::BasicDepth;
Shader* shaders::Shadow_Lab;

Shader* shaders::Everything;
void shaders::InitShaders()
{
	shaders::DefaultObj = new Shader("..\\shaders\\obj_default_vert.shader", "..\\shaders\\obj_default_frag.shader");
	shaders::ShadowMapDepth = new Shader("..\\shaders\\shadow_map_depth_vert.shader", "..\\shaders\\shadow_map_depth_frag.shader");
	shaders::DefaultObjShadows = new Shader("..\\shaders\\obj_default_shadows_vert.shader", "..\\shaders\\obj_default_shadows_frag.shader");
	shaders::BasicDepth = new Shader("..\\shaders\\obj_default_shadows_vert.shader", "..\\shaders\\basicDepth_frag.shader");
	shaders::Shadow_Lab = new Shader("..\\shaders\\ShadowMapping.vs", "..\\shaders\\ShadowMapping.fs");

	shaders::Everything = new Shader("..\\shaders\\postprocess\\default_vert.shader",
		"..\\shaders\\postprocess\\omnishader.shader");
}