#include <glew.h>
#include <iostream>
#include "Terrain.h"
#include "Maths.h"
#include "Shaders.h"

void Terrain::InitBuffer()
{
	for (int i = 0; i < HMImgHeight - 1; i++)
	{
		for (int j = 0; j < HMImgWidth - 1; j++)
		{
			m_Indices.push_back(i * HMImgHeight + j);
			m_Indices.push_back((i + 1) * HMImgHeight + j);
			m_Indices.push_back(i * HMImgHeight + j + 1);

			m_Indices.push_back(i * HMImgHeight + j + 1);
			m_Indices.push_back((i + 1) * HMImgHeight + j);
			m_Indices.push_back((i + 1) * HMImgHeight + j + 1);

		}
	}

	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(3);
	layout.push<float>(2);
	m_VBO.setData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
	m_IBO.setData(m_Indices.data(), m_Indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);
	m_VAO.addBuffer(m_VBO, layout);
}

Terrain::Terrain(const std::string& path)
{
	m_Vertices = LoadHeightmap(path, HMImgWidth, HMImgHeight);

	InitBuffer();
}

void Terrain::Draw()
{

	//glBindVertexArray(hm_VAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hm_IBO);
	//m_Texture1->bind(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture1);

	m_VAO.bind();
	m_IBO.bind();
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_LINES, 0, Heightmap.size());

}

void Terrain::SetTexture1(const std::string& imagePath)
{
	//m_Texture1 = new Texture(imagePath);
	m_Texture1 = Texture::CreateTexture(imagePath);
}

std::vector<Vertex> Terrain::LoadHeightmap(const std::string& path, int& HMImgWidth, int& HMImgHeight)
{
	std::vector<Vertex> heightmap;
	int width, height, nrChannels, hm_height = 1, hm_width = 1;
	stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(path.c_str(), &HMImgWidth, &HMImgHeight, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		//heightmap.resize(HMImgHeight);


		for (int i = 0; i < HMImgHeight; i++)
		{
			for (int j = 0; j < HMImgWidth; j++)
			{
				unsigned char* pixelOffset = data + (i + HMImgHeight * j) * nrChannels;
				unsigned char r = pixelOffset[0];

				heightmap.push_back({
					{((float)hm_height / HMImgHeight) * i, (float)r, ((float)hm_width / HMImgWidth) * j},
					{0.0f, 1.0f, 0.0f},
					glm::vec2((float)j / HMImgWidth , (float)(HMImgHeight - i) / HMImgHeight) * 25.0f
					});

			}
		}

		std::vector< std::vector<std::pair<glm::vec3, glm::vec3>> > tempNormals;
		tempNormals.resize(HMImgHeight);
		for (unsigned int i = 0; i < HMImgHeight; i++)
			tempNormals[i].resize(HMImgWidth);

		for (int i = 0; i < HMImgHeight - 1; i++)
		{
			for (int j = 0; j < HMImgWidth - 1; j++)
			{

				const auto& vertexA = heightmap[i * HMImgHeight + j].Position;
				const auto& vertexB = heightmap[i * HMImgHeight + j + 1].Position;
				const auto& vertexC = heightmap[(i + 1) * HMImgHeight + j + 1].Position;
				const auto& vertexD = heightmap[(i + 1) * HMImgHeight + j].Position;

				const auto triangleNormalA = glm::cross(vertexB - vertexA, vertexA - vertexD);
				const auto triangleNormalB = glm::cross(vertexD - vertexC, vertexC - vertexB);

				tempNormals[i][j] = std::make_pair(glm::normalize(triangleNormalA), glm::normalize(triangleNormalB));


				/*unsigned char* pixelOffset = data + (i + HMImgHeight * j) * nrChannels;
				unsigned char r = pixelOffset[0];

				float L = (j - 1 > 0) ? heightmap[i * HMImgHeight + j - 1].Position.y : 0;
				float R = (j + 1 < HMImgWidth) ? heightmap[i * HMImgHeight + j + 1].Position.y : 0;
				float T = (i - 1 > 0) ? heightmap[(i - 1) * HMImgHeight + j - 1].Position.y : 0;
				float B = (i + 1 > HMImgWidth) ? heightmap[(i + 1) * HMImgHeight + j - 1].Position.y : 0;

				heightmap[i * HMImgHeight + j].Normal = -glm::Normalize(glm::vec3((L - R) / 2, -1, (B - T) / 2));*/

				//std::cout << " " << heightmap[i * HMImgHeight + j].Normal.x << " " << heightmap[i * HMImgHeight + j].Normal.y << " " << heightmap[i * HMImgHeight + j].Normal.z << std::endl;
			}
		}


		for (auto i = 0; i < HMImgHeight; i++)
		{
			for (auto j = 0; j < HMImgWidth; j++)
			{
				const auto isFirstRow = i == 0;
				const auto isFirstColumn = j == 0;
				const auto isLastRow = i == HMImgHeight - 1;
				const auto isLastColumn = j == HMImgWidth - 1;

				auto finalVertexNormal = glm::vec3(0.0f, 0.0f, 0.0f);

				// Look for triangle to the upper-left
				if (!isFirstRow && !isFirstColumn)
				{
					finalVertexNormal += tempNormals[i - 1][j - 1].first;
				}

				// Look for triangles to the upper-right
				if (!isFirstRow && !isLastColumn)
				{

					finalVertexNormal += tempNormals[i - 1][j].first + tempNormals[i - 1][j].second;
				}

				// Look for triangle to the bottom-right
				if (!isLastRow && !isLastColumn)
				{
					finalVertexNormal += tempNormals[i][j].first;
				}

				// Look for triangles to the bottom-right
				if (!isLastRow && !isFirstColumn)
				{
					finalVertexNormal += tempNormals[i][j - 1].first;
					finalVertexNormal += tempNormals[i][j - 1].second;
				}

				// Store final Normal of j-th vertex in i-th row
				//std::swap(finalVertexNormal.y, finalVertexNormal.z);
				//std::swap(finalVertexNormal.y, finalVertexNormal.x);
				//finalVertexNormal.x = -finalVertexNormal.x;
				//finalVertexNormal.y = -finalVertexNormal.y;
				//finalVertexNormal.z = -finalVertexNormal.z;
				heightmap[i * HMImgHeight + j].Normal = -glm::normalize(finalVertexNormal);

				/*std::cout << heightmap[i * HMImgHeight + j].Normal.x << " " <<
					heightmap[i * HMImgHeight + j].Normal.y << " " <<
					heightmap[i * HMImgHeight + j].Normal.z << std::endl;*/
				//heightmap[i * HMImgHeight + j].Normal = glm::vec3(0, 1, 0);

			}
		}


		std::cout << std::endl;


	}
	else {
		std::cout << "Failed to load texture: " << path << std::endl;
	}
	stbi_image_free(data);
	return heightmap;
}