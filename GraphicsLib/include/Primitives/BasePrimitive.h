#pragma once
#include "../stdafx.h"

#include "../Shader.h"

class BasePrimitive
{
public:
	BasePrimitive() = delete;

protected:
	void ApplyModelTransform(Shader& shader) const
	{
		auto rotate = glm::rotate(glm::mat4(1.0f), float((m_angle)*3.14 / 180), glm::vec3(0.0f, 0.0f, 1.0f));
		auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(float(m_width), float(m_height), float(m_depth)));
		auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, m_position.z));
		auto result = trans * rotate * scale;
		shader.Bind();
		shader.SetUniformMatrix4fv("u_model", result);
	}

	void DisableModelTransform(Shader& shader) const
	{
		shader.Bind();
		shader.SetUniformMatrix4fv("u_model", glm::mat4(1.0f));
	}

	float GetWidth()
	{
		return m_width;
	}

	void SetWidth(float newWidth)
	{
		m_width = newWidth;
	}

	void SetHeight(float newHeight)
	{
		m_height = newHeight;
	}

	float GetHeight()
	{
		return m_height;
	}

	BasePrimitive(float width, float height,float depth, glm::vec3 position, float angle = 0.f)
		: m_width(width)
		, m_height(height)
		, m_depth(depth)
		, m_angle(angle)
		, m_position(position)
	{
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

private:
	glm::vec3 m_position;
	float m_width, m_height, m_depth, m_angle;
};
