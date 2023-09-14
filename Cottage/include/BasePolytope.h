#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer/StaticVertexBuffer.h"
#include "IPolytopeDrawable.h"
#include "PolytopeVerticesReader.h"
#include "Primitives/BasePrimitive.h"

class BasePolytope : public IPolytopeDrawable
	, public BasePrimitive
{
public:
	BasePolytope(const std::string& verticesFilePath, size_t verticesNumber, float width, float height, float depth, glm::vec3 position, glm::vec3 angle = { 0.f, 0.f, 0.f })
		: BasePrimitive(width, height, depth, position)
		, m_va()
		, m_vb(GetPoints(verticesFilePath))
		, m_ib(GetIndices(verticesNumber))
	{
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader) const override
	{
		ApplyModelTransform(shader);
		shader.Bind();
		// shader.SetUniform4f("u_color", m_color);
		renderer.Draw(GL_TRIANGLES, m_va, m_ib, shader);
		DisableModelTransform(shader);
	}

private:
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;

	std::vector<PolytopeVertex> GetPoints(const std::string& verticesFilePath)
	{
		PolytopeVerticesReader polytopeReader;
		std::vector<PolytopeVertex> vertices;
		polytopeReader.GetVerticesFromFile(verticesFilePath, vertices);
		std::vector<glm::vec3> normals = CalculateNormals(vertices);
		for (int i = 0; i < normals.size(); i++)
		{
			vertices[i].normals = normals[i];
		}
		return vertices;

		/* std::vector<glm::vec3> normals = CalculateNormals(vertices);

		std::vector<GLfloat> verticesData;
		auto verticesCount = vertices.size();
		for (int i = 0; i < (int)verticesCount; ++i)
		{
			auto vertex = vertices.at(i);
			auto color = colors.at(i);
			auto normal = normals.at(i);
			auto textureCoord = textureCoords.at(i);
			verticesData.insert(verticesData.end(), { vertex.x, vertex.y, vertex.z, color.r, color.g, color.b, normal.x, normal.y, normal.z, textureCoord.x, textureCoord.y });
		}

		SetVerticesData(verticesData);
		UpdateVerticesData();

		SetIndicesData(indices);
		UpdateIndicesData();
		 std::vector<glm::vec2> vertices;

		for (int angle = 0; angle < 360; angle++)
		{
			float rad = static_cast<float>(angle * M_PI / 180.0f);
			// positions
			// vertices.push_back({ topLeftPoint.x + width + cosf(rad) * width, topLeftPoint.y + height + sinf(rad) * height });
			vertices.emplace_back(cosf(rad), sinf(rad));
		}

		return vertices;*/
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
