#include "Models.h"


Model* models::Submarine1;

void models::InitModels()
{
	//models::Submarine1 = new Model("../Assets/Submarines/the_project_941__akula__typhoon_submarine/scene.gltf");
	models::Submarine1 = new Model("../Assets/Submarines/the_project_941__akula__typhoon_submarine_2/914_akula_submarine.gltf");
	//models::Submarine1 = new Model("../Assets/914_akula_submarine.glb");
	//models::Submarine1 = new Model("../Assets/backpack/backpack.obj");
}