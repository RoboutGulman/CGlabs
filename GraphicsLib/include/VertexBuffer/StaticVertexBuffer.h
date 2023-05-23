#pragma once
#include "../Renderer.h"
#include "../Vertex.h"
#include "VertexBuffer.h"

#include <vector>

class StaticVertexBuffer : public VertexBuffer
{
public:
	StaticVertexBuffer(const void* data, unsigned int size)
		: VertexBuffer()
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	template <typename T>
	StaticVertexBuffer(const std::vector<T>& vec)
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(T), &vec[0], GL_STATIC_DRAW));
	}
};
