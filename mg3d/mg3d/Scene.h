#pragma once
#include "Camera.h"
#include <vector>
#include <string>
#include "Skybox.h"
#include "Lighting.h"
//#include "Shader.h"

class Shader;

class Skybox;
class Entity;

class Scene
{
protected:
	Skybox* m_Skybox;

	std::vector<Entity*> m_Entities;

	Light m_PointLight1 = lights::WHITE;

	//vector for the lights
	//(for each type of light, probably)
	//entities vector
public:
	Scene();

	void SetSkybox(const GLuint&);
	
	void SetSkybox(std::vector<std::string>&);

	void PushEntity(Entity*);
	
	virtual void Update();

	virtual void Draw(Camera* pCamera, Shader* shader);
};