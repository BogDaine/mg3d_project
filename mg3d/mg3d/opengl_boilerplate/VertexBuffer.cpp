#include <VertexBuffer.h>

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &ID));

}
VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &ID));
}
VertexBuffer::VertexBuffer(void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &ID));
	bind();
	this->data = data;
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	//std::cout << std::endl << sizeof(data)  << std::endl;
}

void VertexBuffer::setData(void* data, unsigned int size)
{
	bind();
	this->data = data;
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

void VertexBuffer::bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}
