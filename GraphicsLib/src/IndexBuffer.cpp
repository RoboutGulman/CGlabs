#include "../include/stdafx.h"

#include "../include/IndexBuffer.h"
#include "../include/Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_count(count)
{
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const const std::vector<GLuint>& vec)
	: m_count(vec.size())
{
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, vec.size() * sizeof(GLuint), &vec[0], GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
