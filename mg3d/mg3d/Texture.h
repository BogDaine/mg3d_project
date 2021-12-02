#pragma once


#include <GLCall.h>
#include <IndexArray.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <vector>

#include <stb/stb_image.h>

class Texture
{
private:
	unsigned int ID;
	std::string path;
	std::string type;
	std::string fileName;
	int width, height, channels;
	unsigned char* data;
	unsigned int slot = 0;
public:
	Texture();
	Texture(const std::string& file, const unsigned int& slot = 0);
	~Texture();

	void load_from_file(const std::string& file);

	void setUp();

	void bind(const unsigned int& slot);

	void unbind();

	inline std::string getPath() { return path; }

	inline std::string getFileName() { return fileName; }

	inline std::string getType() { return type; }

	//inline std::string getPath(){ return path; }

	inline void setType(std::string t) { type = t; }
};