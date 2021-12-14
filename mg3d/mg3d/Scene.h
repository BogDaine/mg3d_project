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

	GLuint m_DepthMap = 0;
	GLuint m_DepthMapFBO = 0;
	//TO DO:
	//vector for the lights
	//(for each type of light, probably)
	//each with its own Depth Map

public:
	Scene();

	void SetSkybox(const GLuint&);
	
	void SetSkybox(std::vector<std::string>&);

	void PushEntity(Entity*);
	
	//TO DO: make this per-light
	void InitShadowMap();

	virtual void Update();

	virtual void Draw(Camera* pCamera, Shader* shader, const GLuint&);
};