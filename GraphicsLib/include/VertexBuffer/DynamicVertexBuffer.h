#pragma once
#include "../Renderer.h"
#include "VertexBuffer.h"

#include <array>
//наследование излишне
class DynamicVertexBuffer : public VertexBuffer
{
public:
	DynamicVertexBuffer(const void* data, unsigned int size)
		: VertexBuffer()
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	}

	void AddVertices(const std::vector<glm::vec2>& vertices)
	{
		Bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));
	}
};
