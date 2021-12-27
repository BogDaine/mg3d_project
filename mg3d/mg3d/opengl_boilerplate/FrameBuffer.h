#pragma once
#include <GLCall.h>
#include <IndexArray.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <vector>

enum class eFBOTypes
{
	COLOR,
	DEPTH
};

class FrameBuffer
{
	unsigned int m_ID;

	unsigned int m_TextureID;

	unsigned int m_RenderBuffer;

public:
	FrameBuffer(const eFBOTypes& type = eFBOTypes::COLOR);
	~FrameBuffer();
	
	unsigned int GetID();
	unsigned int GetTexture();
	inline const unsigned int GetRenderBuffer() const;

	void Bind();

	void Unbind();

};