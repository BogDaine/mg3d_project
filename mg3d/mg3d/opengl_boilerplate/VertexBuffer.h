#pragma once
#include <GLCall.h>

class VertexBuffer
{
private:
	unsigned int ID;
	void* data;
public:
	VertexBuffer();
	~VertexBuffer();
	VertexBuffer(void* data, unsigned int size);
	void setData(void* data, unsigned int size);
	void bind();
};