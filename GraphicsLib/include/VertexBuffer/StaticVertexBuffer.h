#pragma once
#include "../Renderer.h"
#include "VertexBuffer.h"
#include "../Vertex.h"

#include <vector>

class StaticVertexBuffer : public VertexBuffer
{
public:
	StaticVertexBuffer(const void* data, unsigned int size)
		: VertexBuffer()
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	StaticVertexBuffer(const std::vector<glm::vec2>& vec)
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(glm::vec2), &vec[0], GL_STATIC_DRAW));
	}

	StaticVertexBuffer(const std::vector<glm::vec3>& vec)
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(glm::vec3), &vec[0], GL_STATIC_DRAW));
	}

	StaticVertexBuffer(const std::vector<Vertex>& vec)
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(Vertex), &vec[0], GL_STATIC_DRAW));
	}
};
