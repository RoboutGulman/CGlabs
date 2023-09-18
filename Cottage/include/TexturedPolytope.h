#pragma once
#include "IDrawable.h"
#include <Texture.h>
#include <memory>
#include <string>

class TexturedPolytope : public IDrawable
{
public:
	void Draw(const Renderer& renderer, Shader& shader) const override
	{
		m_texture.Bind();
		m_polytope->Draw(renderer, shader);
	}

protected:
	TexturedPolytope(std::unique_ptr<IDrawable>&& polytope, const std::string& texturePath)
		: m_polytope(std::move(polytope))
		, m_texture(texturePath)
	{
	}

private:
	std::unique_ptr<IDrawable> m_polytope;
	Texture m_texture;
};
