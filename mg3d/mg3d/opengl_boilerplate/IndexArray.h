#pragma once
#include <GLCall.h>

class IndexArray
{
private:
	unsigned int ID;
	unsigned int count = 0;
	unsigned int size = 0;
public:
	IndexArray();
	IndexArray(const void* data, const unsigned int& size);
	void setData(const void* data, const unsigned int& size);
	~IndexArray();

	unsigned int getCount();
	inline unsigned int getSize() { return size; }
	void bind();
	void unbind();

};