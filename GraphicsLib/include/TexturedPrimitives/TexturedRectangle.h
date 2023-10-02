#pragma once
#include "../stdafx.h"

#include "../IndexBuffer.h"
#include "../VertexBuffer/StaticVertexBuffer.h"
#include "../VertexBufferLayout.h"

#include "../Primitives/BasePrimitive.h"
#include "../Texture.h"
#include "VertexWithTextureCoord.h"

class TexturedRectangle : BasePrimitive
{
public:
	TexturedRectangle(glm::vec3 position, float width, float height, const std::string& texturePath, glm::vec4 color)
		: BasePrimitive(width, height, 0, position)
		, m_va()
		, m_vb(GetPoints())
		, m_ib(GetIndices())
		, m_texture(texturePath, GL_TEXTURE_1D)
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec3>(1);
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		ApplyModelTransform(shader);
		m_texture.Bind();
		shader.Bind();
		renderer.Draw(GL_TRIANGLES, m_va, m_ib, shader);
		DisableModelTransform(shader);
	}

private:
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;
	Texture m_texture;

	std::vector<VertexWithTextureCoord> GetPoints()
	{
		return {
			{ { -1.0f,
				  -1.0f,
				  1.0f },
				{ 0.0f,
					1.0f } },
			{ { 1.0f,
				  -1.0f,
				  1.0f },
				{ 1.0f,
					1.0f } },
			{ { 1.0f,
				  1.0f,
				  1.0f },
				{ 1.0f,
					0.0f } },
			{ { -1.0f,
				  1.0f,
				  1.0f },
				{ 0.0f,
					0.0f } }
		};
	}

	std::vector<GLuint> GetIndices()
	{
		return {
			3, 0, 2,
			2, 0, 1
		};
	}
};
