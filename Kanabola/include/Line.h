#pragma once
#include "stdafx.h"

#include "IndexBuffer.h"
#include "Primitives/BasePrimitive.h"
#include "VertexBuffer/StaticVertexBuffer.h"
#include "VertexBufferLayout.h"

class Line : public BasePrimitive
{
public:
	//количество точек не должно называться precision
	Line(float startX, float finishX, unsigned int precision, float width, float height, glm::vec3 position)
		: BasePrimitive(width, height, 0, position, 180)
		, m_va()
		, m_vb(GetPoints(startX, finishX, precision))
		, m_ib(GetIndices(startX, finishX, precision))
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		ApplyModelTransform(shader);
		renderer.Draw(GL_LINE_STRIP, m_va, m_ib, shader);
		DisableModelTransform(shader);
	}

private:
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;

	std::vector<glm::vec2> GetPoints(float startX, float finishX, unsigned int precision)
	{
		std::vector<glm::vec2> vertices;
		float stride = (finishX - startX) / precision;
		for (int i = 0; i <= static_cast<int>(precision); ++i)
		{
			vertices.emplace_back(startX + stride * i, 0);
		}

		return vertices;
	}

	std::vector<GLuint> GetIndices(float startX, float finishX, unsigned int precision)
	{
		std::vector<GLuint> indices;
		for (size_t i = 0; i < precision; ++i)
		{
			indices.push_back(i);
		}
		return indices;
	}
};
