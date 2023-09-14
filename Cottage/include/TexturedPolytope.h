#pragma once
#include "IPolytopeDrawable.h"
#include <Texture.h>
#include <memory>
#include <string>

class TexturedPolytope : public IPolytopeDrawable
{
public:
	void Draw(const Renderer& renderer, Shader& shader) const override
	{
		m_texture.Bind();
		m_polytope->Draw(renderer, shader);
	}

protected:
	TexturedPolytope(std::unique_ptr<IPolytopeDrawable>&& polytope, const std::string& texturePath)
		: m_polytope(std::move(polytope))
		, m_texture(texturePath)
	{
	}

private:
	std::unique_ptr<IPolytopeDrawable> m_polytope;
	Texture m_texture;
};
