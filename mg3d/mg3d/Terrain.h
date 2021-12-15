#pragma once
#include <stb/stb_image.h>
#include <vector>
#include <string>
#include "VertexStruct.h"
#include "VertexArray.h"
#include "IndexArray.h"

class Shader;

class Terrain
{
	std::vector<Vertex> m_Vertices; 
	std::vector<unsigned int> m_Indices;

	int HMImgWidth = 0, HMImgHeight = 0;

	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexArray m_IBO;

	//TO DO:
	//blended textures for each height
	//Terrain Shader


public:
	Terrain(const std::string&);

	void InitBuffer();

	void Draw();


	static std::vector<Vertex> LoadHeightmap(const std::string& LoadHeightmap, int& HMImgWidth, int& HMImgHeight);
};