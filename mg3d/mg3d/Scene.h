#pragma once
#include "Camera.h"
#include <vector>
#include <string>
#include "Skybox.h"
#include "Lighting.h"
//#include "Shader.h"

#include "Terrain.h"

class Shader;

class Skybox;
class Entity;

class Scene
{
protected:
	Skybox* m_Skybox = nullptr;
	Skybox* m_Skybox2 = nullptr;
	Terrain* m_Terrain = nullptr;
	Terrain* m_Water = nullptr;

	bool m_HasTerrain = false;

	glm::vec3 m_TerrainTranslation = { -50.0f, -0.0f, -50.0f };
	glm::vec3 m_TerrainScale = { 100, 0.2, 100 };

	float m_WaterLevel = 45;

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

	float WaterLevel()const;

	bool HasTerrain() const;
	
	void SetSkybox(const GLuint&);
	
	void SetSkybox2(const GLuint&);

	void SetSkybox(std::vector<std::string>&);

	void SetSkybox2(std::vector<std::string>&);
	
	void SetupSeaStuff();

	void SetTerrain(const std::string&);

	void SetTerrain(Terrain*);

	void SetWater(Terrain*);

	void HeightmapInfo(std::vector<Vertex>*& vertices, int& imgWidth, int& imgHeight);

	glm::mat4 TerrainModelMatrix();

	glm::vec3 TerrainTranslation();

	glm::vec3 TerrainScale();

	void PushEntity(Entity*);

	
	//TO DO: make this per-light
	void InitShadowMap();

	virtual void Update();

	virtual void Draw(Camera* pCamera, Shader* shader, const GLuint&, const bool& underwater, const bool& shadowmap = 1);
};