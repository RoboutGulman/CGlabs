#pragma once

#include "VertexBuffer/VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_id;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};