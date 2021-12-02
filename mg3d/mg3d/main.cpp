#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Shader.h"

#include "glfwstuff.h"

#include "Models.h"
#include "Shaders.h"

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

	WindowLoop(window, scene, pCamera);

    return 0;
}