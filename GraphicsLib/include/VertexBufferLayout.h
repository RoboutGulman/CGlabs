#pragma once
#include "stdafx.h"

#include "GL/glew.h"
#include "Renderer.h"
#include "Vertex.h"
#include <stdexcept>
#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char isNormalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;

public:
	VertexBufferLayout()
		: m_stride(0)
	{
	}

	template <typename T>
	void Push(unsigned int count)
	{
		std::runtime_error(false);
	}

	template <>
	void Push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template <>
	void Push<glm::vec2>(unsigned int /* count */)
	{
		Push<float>(2);
	}

	template <>
	void Push<glm::vec3>(unsigned int /* count */)
	{
		Push<float>(3);
	}

	template <>
	void Push<Vertex>(unsigned int /* count */)
	{
		Push<float>(3);
		Push<float>(4);
	}

	template <>
	void Push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template <>
	void Push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const
	{
		return m_elements;
	}
	inline unsigned int GetStride() const { return m_stride; }
};
