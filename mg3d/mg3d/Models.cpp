#include "Models.h"


Model* models::Submarine1;
Model* models::Coral1;
Model* models::Coral2;

void models::InitModels()
{
	models::Submarine1 = new Model("../Assets/Submarines/the_project_941__akula__typhoon_submarine_2/914_akula_submarine.gltf");
	models::Coral1 = new Model("../Assets/models/seastuff/tree_coral/tree_coral.obj");
	models::Coral2 = new Model("../Assets/models/seastuff/red_coral/red_coral.obj");
}