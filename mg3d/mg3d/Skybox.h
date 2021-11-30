#pragma once
#include "Shader.h"
#include "Renderer.h"
#include "Camera.h"

class Skybox
{
protected:

	GLuint m_TextureID;

public:
	Skybox(const GLuint& texture);

	Skybox(std::vector<std::string>&);
	
	~Skybox();

	void Draw(Camera*);
	
	static GLuint LoadCubemap(std::vector<std::string>&);
	
};