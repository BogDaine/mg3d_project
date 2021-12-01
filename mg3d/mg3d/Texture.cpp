
#include <iostream>

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


Texture::Texture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLCall(glGenTextures(1, &ID));
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

}

Texture::Texture(const std::string& file, const unsigned int& slot)
{
	this->slot = slot;

	path = file;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLCall(glGenTextures(1, &ID));
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	load_from_file(path);
	setUp();
	unbind();

	//if (data)
	//{
	//	if (channels == 4)
	//	{
	//		//std::cout << "texture has " << channels << " channels" << std::endl;
	//		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	//	}
	//	if (channels == 3)
	//	{
	//		//std::cout << "texture has " << channels << " channels" << std::endl;
	//		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
	//	}
	//		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	//}
	//else
	//	std::cout << "[ERROR]: Failed to load texture!" << std::endl;

	//stbi_image_free(data);
	//unbind();

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &ID));
}

void Texture::load_from_file(const std::string& file)
{
	stbi_set_flip_vertically_on_load(true);
	path = file;
	fileName = path.substr(path.find_last_of('/') + 1);
	data = NULL;
	data = stbi_load(file.c_str(), &width, &height, &channels, 0);
}

void Texture::setUp()
{
	if (data)
	{
		if (channels == 4)
		{
			//std::cout << "texture has " << channels << " channels" << std::endl;
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		}
		if (channels == 3)
		{
			//std::cout << "texture has " << channels << " channels" << std::endl;
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		}
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
		std::cout << "[ERROR]: Failed to load texture!" << std::endl;

	stbi_image_free(data);
	unbind();
}

void Texture::bind(const unsigned int& slot)
{
	this->slot = slot;

	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));
}

void Texture::unbind()
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
