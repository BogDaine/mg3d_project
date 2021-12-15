#pragma once
#include <stb/stb_image.h>
#include <vector>
#include <string>
#include "VertexStruct.h"
#include "VertexArray.h"
#include "IndexArray.h"

#include "Texture.h"

class Shader;

class Terrain
{
	std::vector<Vertex> m_Vertices; 
	std::vector<unsigned int> m_Indices;

	int HMImgWidth = 0, HMImgHeight = 0;

	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexArray m_IBO;

	//Texture *m_Texture1 = nullptr;
	
	unsigned int m_Texture1 = 0;
	//TO DO:
	//blended textures for each height
	//Terrain Shader


public:
	Terrain(const std::string&);

	void InitBuffer();

	void Draw();

	void SetTexture1(const std::string&);

	static std::vector<Vertex> LoadHeightmap(const std::string& LoadHeightmap, int& HMImgWidth, int& HMImgHeight);
};