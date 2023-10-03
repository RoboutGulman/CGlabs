#pragma once
#include "IDrawable.h"
#include "PolytopeVerticesReader.h"
#include "Primitives/BasePrimitive.h"
#include "VertexBuffer/StaticVertexBuffer.h"
#include "VertexBufferLayout.h"

class BasePolytope : public IDrawable
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

	std::vector<glm::vec3> CalculateNormals(const std::vector<PolytopeVertex>& vertices) const
	{
		std::vector<glm::vec3> normals;
		auto vertexCount = vertices.size();
		for (size_t i = 0; i < vertexCount; i += 3)
		{
			auto firstVector = glm::vec3(vertices[i + 1].coordinates.x - vertices[i].coordinates.x, vertices[i + 1].coordinates.y - vertices[i].coordinates.y, vertices[i + 1].coordinates.z - vertices[i].coordinates.z);
			auto secondVector = glm::vec3(vertices[i + 2].coordinates.x - vertices[i].coordinates.x, vertices[i + 2].coordinates.y - vertices[i].coordinates.y, vertices[i + 2].coordinates.z - vertices[i].coordinates.z);

			auto normal = glm::cross(firstVector, secondVector);
			normal = glm::normalize(normal);

			normals.push_back({ normal.x, normal.y, normal.z });
			normals.push_back({ normal.x, normal.y, normal.z });
			normals.push_back({ normal.x, normal.y, normal.z });
		}

		return normals;
	}
};
