#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Shader.h"

#include "glfwstuff.h"

#include "Models.h"
#include "Shaders.h"
#include "Submarine.h"

//TO DO: Submarine controls
//TO DO: ShadowMapping
//
//TO DO: Physics
//
//TO DO: Terrain (heightmap, probably)
//TO DO: Water
// 
//TO DO: The posibility of binding the camera to a submarine
//TO DO: Fishies! :)

int main()
{
	GLFWwindow* window;
	InitWindow(window, "titlu imaginativ");

    //Placeholder code.
    //Will modify later
    //Like functions for scene initialization and whatnot

	Scene scene;
	int width, height;
	glfwGetWindowSize(window, &width, &height);
    Camera* pCamera = new Camera(width, height, glm::vec3(0.0f, 1.0f, 7.0f));

    InputHandler input(window, pCamera);

    std::vector<std::string> faces
    {
            "skybox/right.jpg",
            "skybox/left.jpg",
            "skybox/top.jpg",
            "skybox/bottom.jpg",
            "skybox/front.jpg",
            "skybox/back.jpg"
    };

    models::InitModels();
    shaders::InitShaders();

    


    scene.SetSkybox(faces);
    Submarine DummySubmarine({ 0, 0, 0 });
    scene.PushEntity(&DummySubmarine);

    DummySubmarine.Rotate(glm::radians(-90.0f), 0, glm::radians(90.0f));

	WindowLoop(window, scene, pCamera, &input);

    return 0;
}