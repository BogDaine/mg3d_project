#include "Models.h"


Model* models::Submarine1 = nullptr;
Model* models::Coral1 = nullptr;
Model* models::Coral2 = nullptr;
Model* models::Fish1 = nullptr;
Model* models::Fish2 = nullptr;
Model* models::Turtle = nullptr;
Model* models::Dolphin = nullptr;
Model* models::Fish3 = nullptr;
Model* models::Fish4 = nullptr;
Model* models::Octopus = nullptr;

void models::InitModels()
{
	models::Submarine1 = new Model("../Assets/Submarines/the_project_941__akula__typhoon_submarine_2/914_akula_submarine.gltf");
	models::Coral1 = new Model("../Assets/models/seastuff/tree_coral/tree_coral.obj");
	models::Coral2 = new Model("../Assets/models/seastuff/red_coral/red_coral.obj");
	models::Fish1 = new Model("../Assets/models/seastuff/low_poly_fish/scene.gltf");
	models::Fish2 = new Model("../Assets/models/seastuff/opah_fish/scene.gltf");
	models::Turtle = new Model("../Assets/models/seastuff/sea_turtle/10042_Sea_Turtle_V2_iterations-2.obj");
	models::Dolphin = new Model("../Assets/models/seastuff/dolphin/10014_dolphin_v2_max2011_it2.obj");
	models::Fish3 = new Model("../Assets/models/seastuff/blue_fish/13006_Blue_Tang_v1_l3.obj");
	models::Fish4 = new Model("../Assets/models/seastuff/yellow_fish/13008_Clown_Goby_Citrinis_v1_l3.obj");
	models::Octopus = new Model("../Assets/models/seastuff/octopus/13013_Red_Head_Solon_Fairy_Wrasse_v1_l3.obj");
}