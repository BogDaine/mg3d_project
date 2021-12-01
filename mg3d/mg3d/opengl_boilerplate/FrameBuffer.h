#pragma once
#include <GLCall.h>
#include <IndexArray.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <vector>

class FrameBuffer
{
	unsigned int m_ID;
	unsigned int m_TextureID;

	unsigned int m_RenderBuffer;

public:
	FrameBuffer();
	~FrameBuffer();
	
	inline const unsigned int GetID() const;
	inline const unsigned int GetTexture() const;
	inline const unsigned int GetRenderBuffer() const;

	void Bind();

	void Unbind();

};