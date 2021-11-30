#pragma once
#include "Camera.h"
#include <vector>
#include <string>
#include "Skybox.h"

class Skybox;

class Scene
{
protected:
	Skybox* m_Skybox;
	//vector for the lights
	//(for each type of light, probably)
	//entities vector
public:
	Scene();

	void SetSkybox(const GLuint&);
	
	void SetSkybox(std::vector<std::string>&);
	
	void Update();

	virtual void Draw(Camera* pCamera);
};