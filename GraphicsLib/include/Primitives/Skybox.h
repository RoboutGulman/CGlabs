#pragma once
#include "../stdafx.h"

#include "../CubemapTexture.h"
#include "../VertexArray.h"
#include "../VertexBuffer/StaticVertexBuffer.h"
#include "../VertexBufferLayout.h"
#include <string>
#include <vector>

class Skybox
{
public:
	Skybox(float size, const std::vector<std::string>& faces)
		: m_va()
		, m_vb(GetPoints(size))
		, m_ib(GetIndices(VERTEX_COUNT))
		, m_cubemapTexture(faces)
	{
		m_va.Bind();
		m_cubemapTexture.Bind();

		VertexBufferLayout layout;
		layout.Push<glm::vec3>(1);
		m_va.AddBuffer(m_vb, layout);

		m_va.Unbind();
		m_cubemapTexture.Unbind();
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		m_cubemapTexture.Bind();
		renderer.Draw(GL_TRIANGLES, m_va, m_ib, shader);
	}

private:
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;
	static const unsigned int VERTEX_COUNT = 36;

	CubemapTexture m_cubemapTexture;

	std::vector<glm::vec3> GetPoints(float size)
	{
		std::vector<glm::vec3> vertices = {
			{ -1.0f, 1.0f, -1.0f },
			{ -1.0f, -1.0f, -1.0f },
			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, 1.0f, -1.0f },
			{ -1.0f, 1.0f, -1.0f },

			{ -1.0f, -1.0f, 1.0f },
			{ -1.0f, -1.0f, -1.0f },
			{ -1.0f, 1.0f, -1.0f },
			{ -1.0f, 1.0f, -1.0f },
			{ -1.0f, 1.0f, 1.0f },
			{ -1.0f, -1.0f, 1.0f },

			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, -1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, -1.0f },
			{ 1.0f, -1.0f, -1.0f },

			{ -1.0f, -1.0f, 1.0f },
			{ -1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f },
			{ 1.0f, -1.0f, 1.0f },
			{ -1.0f, -1.0f, 1.0f },

			{ -1.0f, 1.0f, -1.0f },
			{ 1.0f, 1.0f, -1.0f },
			{ 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f },
			{ -1.0f, 1.0f, 1.0f },
			{ -1.0f, 1.0f, -1.0f },

			{ -1.0f, -1.0f, -1.0f },
			{ -1.0f, -1.0f, 1.0f },
			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, -1.0f, -1.0f },
			{ -1.0f, -1.0f, 1.0f },
			{ 1.0f, -1.0f, 1.0f }
		};
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i] *= size;
		}
		return vertices;
	}

	std::vector<GLuint> GetIndices(size_t size)
	{
		std::vector<GLuint> indices;
		for (size_t i = 0; i < size; ++i)
		{
			indices.emplace_back(i);
		}
		return indices;
	}
};
