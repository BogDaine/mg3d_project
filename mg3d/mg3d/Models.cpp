#include "Models.h"


Model* models::Submarine1;

void models::InitModels()
{
	models::Submarine1 = new Model("../Assets/Submarines/the_project_941__akula__typhoon_submarine/scene.gltf");
	//models::Submarine1 = new Model("../Assets/backpack/backpack.obj");
}