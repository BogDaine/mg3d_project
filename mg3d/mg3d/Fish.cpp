#include "Fish.h"
#include "Utility.h"

Fish::Fish(Model *model, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale, const float& speed, const glm::vec3& velocity):
	VisibleEntity(model, pos, rot, scale)
{
	m_Speed = speed;
	m_Velocity = velocity;
}

void Fish::Update()
{
	ExertVelocity();
	if (m_SceneRef->HasTerrain())
	{
		CollisionCheck();
		if (m_Pos.y > m_SceneRef->WaterLevel())
		{
			m_Pos.y = m_SceneRef->WaterLevel();

			m_Velocity = m_Velocity * glm::vec3
			(
				util::random_float(-1.5f, 1.5f),
				util::random_float(-1.5f, 1.5f),
				util::random_float(-1.5f, 1.5f)
			);
		}
	}

	Rotate(
		util::random_float(-0.01f, 0.01f),
		util::random_float(0.0f, 0.003f),
		util::random_float(0.0f, 0.003f)
	);

	this->VisibleEntity::Update();
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(-90.0f), { 1,0,0 });
	//m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(180.0f), { 0,1,0 });
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(90.0f), { 0,0,1 });
}

void Fish::CollisionCheck()
{

	std::vector<Vertex>* HeightMap;
	int imgWidth, imgHeight;
	m_SceneRef->HeightmapInfo(HeightMap, imgWidth, imgHeight);

	float TerrainHeight;

	float terrainX = (m_Pos.x / m_SceneRef->TerrainScale().x) * imgWidth - m_SceneRef->TerrainTranslation().x / m_SceneRef->TerrainScale().x * imgWidth;
	float terrainZ = (m_Pos.z / m_SceneRef->TerrainScale().z) * imgHeight - m_SceneRef->TerrainTranslation().z / m_SceneRef->TerrainScale().z * imgHeight;

	if (terrainX < imgWidth && terrainX >= 0 && terrainZ < imgHeight && terrainZ > 0)
	{
		TerrainHeight = HeightMap->operator[]((int)terrainX* imgWidth + terrainZ).Position.y * m_SceneRef->TerrainScale().y;
		if (m_Pos.y < TerrainHeight + 0.02)
		{
			m_Pos.y = TerrainHeight + 0.02;
			m_Velocity = m_Velocity * glm::vec3
			(
				util::random_float(-1.5f, 1.5f),
				util::random_float(-1.5f, 1.5f),
				util::random_float(-1.5f, 1.5f)
			);
		}
	}
}