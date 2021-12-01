#include "FrameBuffer.h"
#include "../Cfg.h"

#include <iostream>

FrameBuffer::FrameBuffer()
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cfg::GetWindowWidth(), cfg::GetWindowHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

	glGenRenderbuffers(1, &m_RenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, cfg::GetWindowWidth(), cfg::GetWindowHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);


	// Error checking framebuffer
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << fboStatus << std::endl;

}

FrameBuffer::~FrameBuffer()
{
	glDeleteRenderbuffers(1, &m_RenderBuffer);
	glDeleteFramebuffers(1, &m_ID);
}

inline const unsigned int FrameBuffer::GetID() const
{
	return m_ID;
}

inline const unsigned int FrameBuffer::GetTexture() const
{
	return m_TextureID;
}

inline const unsigned int FrameBuffer::GetRenderBuffer() const
{
	return m_RenderBuffer;
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
