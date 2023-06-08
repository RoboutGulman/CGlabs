#pragma once
#include "stdafx.h"

#include "IndexBuffer.h"
#include "Vertex.h"
#include "VertexBuffer/StaticVertexBuffer.h"
#include "VertexBufferLayout.h"
//использовать константные методы
class SnubDodecahedron
{
public:
	SnubDodecahedron()
		: m_va()
		, m_vb(GetPoints())
		, m_ib(GetIndices(VERTEX_COUNT))
	{
		VertexBufferLayout layout;
		layout.Push<Vertex>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		renderer.Draw(GL_TRIANGLES, m_va, m_ib, shader);
	}

private:
	static const unsigned int VERTEX_COUNT = 900;

	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;

	std::vector<Vertex> GetPoints()
	{
		return GetVerticesFromFile("res/SnubDodecahedron.txt");
	}

	std::vector<GLuint> GetIndices(size_t size)
	{
		std::vector<GLuint> indices;
		for (size_t i = 0; i < size; ++i)
		{
			indices.push_back(i);
		}
		return indices;
	}
};
