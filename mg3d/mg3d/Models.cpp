#include "Models.h"


Model* models::Submarine1 = nullptr;
Model* models::Coral1 = nullptr;
Model* models::Coral2 = nullptr;
Model* models::Fish1 = nullptr;
Model* models::Fish2 = nullptr;

void models::InitModels()
{
	models::Submarine1 = new Model("../Assets/Submarines/the_project_941__akula__typhoon_submarine_2/914_akula_submarine.gltf");
	models::Coral1 = new Model("../Assets/models/seastuff/tree_coral/tree_coral.obj");
	models::Coral2 = new Model("../Assets/models/seastuff/red_coral/red_coral.obj");
	models::Fish1 = new Model("../Assets/models/seastuff/low_poly_fish/scene.gltf");
	models::Fish2 = new Model("../Assets/models/seastuff/opah_fish/scene.gltf");
}