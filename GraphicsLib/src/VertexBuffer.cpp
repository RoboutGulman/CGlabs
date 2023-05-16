#include "../include/stdafx.h"

#include "../include/Renderer.h"
#include "../include/VertexBuffer/VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
